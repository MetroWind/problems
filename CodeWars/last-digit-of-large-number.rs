// https://www.codewars.com/kata/5511b2f550906349a70004e1/

static LAST_DIGITS: [[u8; 4];10] = [
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

fn last2Last(digit: u8, power_mod4: u8, power_is_zero: bool, power_is_one: bool) -> u8
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

fn last_digit(str1: &str, str2: &str) -> i32
{
    let last: u8 = str1[(str1.len() - 1)..].parse().unwrap();
    let power_mod4: u8 = if str2.len() > 1
    { (str2[(str2.len() - 2)..].parse::<u16>().unwrap() % 4) as u8 }
    else
    { str2[(str2.len() - 1)..].parse::<u8>().unwrap() % 4 };

    last2Last(last, power_mod4, str2 == "0", str2 == "1") as i32
}
