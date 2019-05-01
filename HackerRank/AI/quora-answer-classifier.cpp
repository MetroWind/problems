// https://www.hackerrank.com/challenges/quora-answer-classifier

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <numeric>
#include <functional>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

class TimeLog
{
private:
    timeval Begin;
    timeval Genesis;
    std::string LastEntry;
    unsigned long TotalTime;
    std::ostream& File;
public:
    TimeLog() : File{std::cerr}
    {
        gettimeofday(&Genesis, 0);
        TotalTime = 0;
    }
    ~TimeLog() {}

    unsigned long operator() (const std::string& entry)
    {
        unsigned long Time = 0;
        timeval End;
        if(!(LastEntry.empty()))
        {
            gettimeofday(&End, 0);
            Time = ((End.tv_sec - Begin.tv_sec) * 1000000 +
                    (End.tv_usec - Begin.tv_usec)) / 1000;
            File << "[TimeLog: " << LastEntry << "] " << Time << "ms" << std::endl;
            TotalTime += Time;
        }
        gettimeofday(&Begin, 0);
        File << entry << "..." << std::endl;
        LastEntry = entry;
        return Time;
    }

    unsigned long operator() ()
    {
        unsigned long Time = 0;
        timeval End;
        if(!(LastEntry.empty()))
        {
            gettimeofday(&End, 0);
            Time = ((End.tv_sec - Begin.tv_sec) * 1000000 +
                    (End.tv_usec - Begin.tv_usec)) / 1000;
            File << "[TimeLog: " << LastEntry << "] " << Time << "ms" << std::endl;
            TotalTime += Time;
        }
        LastEntry = std::string();
        return Time;
    }

    unsigned long doom(const std::string& name) const
    {
        unsigned long Time = 0;
        timeval End;
        gettimeofday(&End, 0);
        Time = ((End.tv_sec - Genesis.tv_sec) * 1000000 +
                (End.tv_usec - Genesis.tv_usec)) / 1000;
        File << "[TimeLog: " << name << " (elapsed)] " << Time << "ms" << std::endl;
        File << "[TimeLog: " << name << " (total)] " << TotalTime << "ms" << std::endl;
        return Time;
    }
};

std::vector<std::string> strSplit(const std::string& str,
                                  const std::string& delim)
{
    std::string s = str;
    size_t pos = 0;
    std::string token;
    std::vector<std::string> Splitted;

    while ((pos = s.find(delim)) != std::string::npos)
    {
        token = s.substr(0, pos);
        Splitted.push_back(token);
        s.erase(0, pos + delim.length());
    }
    Splitted.push_back(s);

    return Splitted;
}

double average(const std::vector<double>& xs)
{
    return std::accumulate(std::begin(xs), std::end(xs), 0, std::plus<double>()) /
        double(xs.size());
}

double stdDev(const std::vector<double>& xs, double avg)
{
    double& Avg = avg;
    double Sum = 0.0;
    for(auto& x: xs)
    {
        double d = x - Avg;
        Sum += d*d;
    }
    return sqrt(Sum / double(xs.size()));
}

double stdDev(const std::vector<double>& xs)
{
    return stdDev(xs, average(xs));
}

struct Normalization
{
    double Avg;
    double StdDev;
    double normalize(double x) const
    {
        if(StdDev != 0.0)
            return (x - Avg) / StdDev;
        else
            return x;
    }
};

class TrainingSample
{
private:
    std::vector<double> Xs;
public:
    std::string Id;
    double Target;

    TrainingSample(const std::vector<double>& xs, double t)
            : Xs{xs}, Target{t} {}
    TrainingSample(std::size_t size) : Xs(size), Target{0.0} {}
    TrainingSample(const TrainingSample& s) : Xs{s.Xs}, Target{s.Target} {}
    TrainingSample& operator=(TrainingSample rhs)
    {
        std::swap(*this, rhs);
        return *this;
    }
    ~TrainingSample() {}

    double target() const
    {
        return Target;
    }

    const std::vector<double>& xs() const
    {
        return Xs;
    }
    std::vector<double>& xs()
    {
        return Xs;
    }

    std::size_t nDims() const
    {
        return Xs.size();
    }
};

std::ostream& operator<<(std::ostream& os, const TrainingSample& s)
{
    os << s.Id << ' ' << s.Target << ' ';
    for(std::size_t i = 0; i < s.nDims(); i++)
    {
        os << i+1 << ':' << s.xs()[i];
        if(i < s.nDims() - 1)
            os << ' ';
    }
    return os;
}

void applyNormalization(std::vector<TrainingSample>& samples,
                        const std::vector<Normalization>& norms)
{
    for(std::size_t iDim = 0; iDim < samples[0].nDims(); iDim++)
    {
        for(std::size_t i = 0; i < samples.size(); i++)
        {
            double X = samples[i].xs()[iDim];
            samples[i].xs()[iDim] = norms[iDim].normalize(X);
        }
    }
}

void normalize(std::vector<TrainingSample>& samples,
               std::vector<Normalization>& norms)
{
    norms.resize(samples[0].nDims());
    for(std::size_t iDim = 0; iDim < samples[0].nDims(); iDim++)
    {
        std::vector<double> Feature(samples.size());
        for(std::size_t i = 0; i < samples.size(); i++)
        {
            Feature[i] = samples[i].xs()[iDim];
        }
        norms[iDim].Avg = average(Feature);
        norms[iDim].StdDev = stdDev(Feature, norms[iDim].Avg);
    }

    applyNormalization(samples, norms);
}

double dot(const std::vector<double>& xs, const std::vector<double>& ys)
{
    double Sum = 0.0;
    for(unsigned int i = 0; i < xs.size(); i++)
    {
        Sum += xs[i] * ys[i];
    }
    return Sum;
}

double mod(const std::vector<double>& xs)
{
    double Sum = 0.0;
    for(auto& x: xs)
    {
        Sum += x*x;
    }
    return sqrt(Sum);
}

double logistic(const std::vector<double>& ws, const std::vector<double>& xs)
{
    return 1.0 / (1.0 + exp(-1.0 * dot(ws, xs)));
}

void train(std::vector<double>& ws, const std::vector<TrainingSample>& Samples,
           double eta)
{
    std::vector<double> Delta(ws.size(), 0.0);
    for(auto& Sample: Samples)
    {
        double y = logistic(ws, Sample.xs());
        double Err = Sample.target() - y;
        for(std::size_t i = 0; i < ws.size(); i++)
        {
            Delta[i] = eta * Err * Sample.xs()[i];
        }
        // If we update ws now, it's online learning.
        for(std::size_t i = 0; i < ws.size(); i++)
        {
            ws[i] += Delta[i];
        }
    }
    // If we update ws here, it's batch learning.
    return;
}

void loadTrain(std::vector<TrainingSample>& samples, std::istream& in)
{
    std::string Line;
    std::getline(in, Line);
    std::vector<std::string> Segs = strSplit(Line, " ");
    std::size_t NSamples = std::stoi(Segs[0]);
    std::size_t NDims = std::stoi(Segs[1]);

    samples.resize(NSamples, TrainingSample(NDims));
    for(std::size_t i = 0; i < NSamples; i++)
    {
        std::vector<double> Input(NDims);
        std::getline(in, Line);
        Segs = strSplit(Line, " ");
        samples[i].Id = Segs[0];
        samples[i].Target = std::stoi(Segs[1]);

        for(std::size_t j = 0; j < NDims; j++)
        {
            std::vector<std::string> SubSegs = strSplit(Segs[j+2], ":");
            std::size_t Idx = std::stoi(SubSegs[0]) - 1;
            samples[i].xs()[Idx] = std::stod(SubSegs[1]);
        }
    }
}

void loadQuery(std::vector<TrainingSample>& queries, std::istream& in, std::size_t n_dims)
{
    std::string Line;
    std::getline(in, Line);
    std::size_t Count = std::stoi(Line);
    queries.resize(Count, TrainingSample(n_dims));

    for(std::size_t i = 0; i < Count; i++)
    {
        std::vector<double> Input(n_dims);
        std::getline(in, Line);
        std::vector<std::string> Segs = strSplit(Line, " ");
        queries[i].Id = Segs[0];

        for(std::size_t j = 0; j < n_dims; j++)
        {
            std::vector<std::string> SubSegs = strSplit(Segs[j+1], ":");
            std::size_t Idx = std::stoi(SubSegs[0]) - 1;
            queries[i].xs()[Idx] = std::stod(SubSegs[1]);
        }
    }
}

int predict(const std::vector<double>& ws, const std::vector<double>& xs)
{
    if(logistic(ws, xs) > 0.0)
        return 1;
    else
        return -1;
}

int main()
{
    TimeLog Log;

    std::vector<TrainingSample> Samples, Queries;
    Log("Loading training data");
    loadTrain(Samples, std::cin);
    std::vector<Normalization> Norms;
    Log("Normalizing training data");
    normalize(Samples, Norms);

    // for(auto& s: Samples)
    // {
    //     std::cerr << s << std::endl;
    // }

    std::size_t NDims = Samples[0].nDims();
    Log("Loading query data");
    loadQuery(Queries, std::cin, NDims);
    Log("Normalizing query data");
    applyNormalization(Queries, Norms);

    std::vector<double> Ws(NDims, 0.0);
    double Eta = 0.1;
    Log("Training");
    for(int i = 0; i < 20; i++)
    {
        train(Ws, Samples, Eta);
        std::cerr << i+1 << ' ' << mod(Ws) << std::endl;
    }

    Log("Outputing");
    for(auto& Query: Queries)
    {
        std::cout << Query.Id << ' ' << std::showpos << predict(Ws, Query.xs())
                  << std::endl;
    }

    Log.doom("Total");
    return 0;
}
