#include <cs50.h>
#include <stdio.h>
#include <math.h>

int is_valid(long long number, int len);
string verify_bank(long long number, int len);
int get_first_digits(long long number, int len, int n_digits);
int len_of_number(long long number);

int main(void)
{
    long long cc_number;

    // ask for credit card number
    do {
    printf("Number: ");
    cc_number = get_long_long();
    } while (cc_number <= 0);
    
    // find len of cc_number
    int len = len_of_number(cc_number);
    
    if (is_valid(cc_number, len)) {
        string bank = verify_bank(cc_number, len);
        printf("%s\n", bank);
    } else {
        printf("INVALID\n");
    }
    
    return 0;
}

int len_of_number(long long number) {
    return floor(log10(number)) + 1;
}

int is_valid(long long number, int len) {
    // iterate over all digits of the number and do the math
    int checksum = 0;
    int digit; // the current digit in the loop
    for (int i = 0; i < len; i++) {
        digit = number % 10;
        if (i % 2 == 1) {
            digit *= 2;
            // sum the digits of that product and write it to int checksum
            // check if two digits or one
            if (digit / 10 == 0) {
                checksum += digit;
            } else {
                checksum += (digit / 10 + digit % 10);
            }
        } else {
            checksum += digit;    
        }
        number /= 10;
    }
    
    if (number % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

int get_first_digits(long long number, int len, int n_digits) {
    for (int i = 0; i < len - n_digits; i++) {
        number /= 10;
    }
    return (int) number;
}

string verify_bank(long long number, int len) {
    int f1d = get_first_digits(number, len, 1);
    int f2d = get_first_digits(number, len, 2);
    
    string bank;
    
    switch (len) {
        case 13: {
            if (f1d == 4) {
                bank = "VISA";
                break;
            }
        }
        case 15: {
            if (f2d == 34 || f2d == 37) {
                bank = "AMEX";
                break;
            }
        }
        case 16: {
            if (f1d == 4) {
                bank = "VISA";
                break;
            } else if (f2d == 51 || f2d == 52 || f2d == 53 || f2d == 54 || f2d == 55) {
                bank = "MASTERCARD";
                break;
            }
        }
        default:
            return "INVALID";
    }
    
    return bank;
}