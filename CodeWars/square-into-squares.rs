// https://www.codewars.com/kata/54eb33e5bc1a25440d000891

fn decomposeInner(sum: i64, start: i64) -> Vec<i64>
{
    let mut result = vec![];

    for x in (1..=start).rev()
    {
        let this = x * x;
        if this == sum
        {
            result.push(x);
            return result;
        }
        else if this < sum
        {
            result = decomposeInner(sum - this, x - 1);
            if result.is_empty()
            {
                continue;
            }
            result.push(x);
            return result;
        }
    }
    result
}

fn decompose(n: i64) -> Option<Vec<i64>>
{
    let sum = n * n;

    let result = decomposeInner(sum, n-1);
    if result.is_empty()
    {
        return None;
    }
    else
    {
        return Some(result);
    }
}
