// https://www.codewars.com/kata/5518a860a73e708c0a000027

#![allow(unused_parens)]
#![allow(non_snake_case)]

static LAST_DIGITS: [[u64; 4];10] = [
    [0, 0, 0, 0],               // 0
    [1, 1, 1, 1],               // 1
    [6, 2, 4, 8],               // 2
    [1, 3, 9, 7],               // 3
    [6, 4, 0, 0],               // 4
    [5, 0, 0, 0],               // 5
    [6, 0, 0, 0],               // 6
    [1, 7, 9, 3],               // 7
    [6, 8, 4, 2],               // 8
    [1, 9, 0, 0],               // 9
];

fn last2Last(digit: u64, power_mod4: u64, power_is_zero: bool, power_is_one: bool) -> u64
{
    if power_is_zero
    {
        return 1;
    }

    if power_is_one
    {
        return digit;
    }

    // println!("Calculating xx{}^(4n+{})...", digit, power_mod4);
    match digit
    {
        0 => 0,
        1 | 5 | 6 => digit,
        2 | 3 | 7 | 8 => LAST_DIGITS[digit as usize][power_mod4 as usize],
        4 | 9 => LAST_DIGITS[digit as usize][(power_mod4 % 2) as usize],
        _ => 0,
    }
}

fn mod4OfPower(base: u64, power_last_digit: u64, power_is_one: bool) -> u64
{
    match base % 4
    {
        0 => 0,
        1 => 1,
        2 => if power_is_one {2} else {0},
        3 => if power_last_digit % 2 == 0 {1} else {3},
        _ => unreachable!(),
    }
}

fn last_digit(lst: &[u64]) -> u64
{
    // println!("Calculating for {:?}...", lst);
    if lst.is_empty()
    {
        return 1;
    }

    let mut last = lst.last().unwrap() % 10;
    let mut last_last = last;
    let mut power_mod4 = lst.last().unwrap() % 4;
    let mut power_is_zero = (lst.last().unwrap().clone() == 0);
    let mut power_is_one = (lst.last().unwrap().clone() == 1);

    for i in (0..lst.len()-1).rev()
    {
        // println!("Last digit is {}.", last);
        // if power_is_zero
        // {
        //     println!("Power is 0.");
        // }
        // if power_is_one
        // {
        //     println!("Power is 1.");
        // }

        last = last2Last(lst[i] % 10, power_mod4, power_is_zero, power_is_one);
        power_mod4 = mod4OfPower(lst[i], last_last, power_is_one);
        power_is_one = (power_is_zero || lst[i] == 1);
        power_is_zero = (lst[i] == 0 && !power_is_zero);
        last_last = last;
    }
    // println!("Last digit is {}.", last);
    last
}
