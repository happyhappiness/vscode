static char *etag_ulong_to_hex(char *next, unsigned long u)
{
    int printing = 0;
    int shift = sizeof(unsigned long) * 8 - 4;
    do {
        unsigned long next_digit = ((u >> shift) & (unsigned long)0xf);
        if (next_digit) {
            *next++ = HEX_DIGITS[next_digit];
            printing = 1;
        }
        else if (printing) {
            *next++ = HEX_DIGITS[next_digit];
        }
        shift -= 4;
    } while (shift);
    *next++ = HEX_DIGITS[u & (unsigned long)0xf];
    return next;
}