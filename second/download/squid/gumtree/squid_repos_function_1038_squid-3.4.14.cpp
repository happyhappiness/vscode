static void parseBytesOptionValue(size_t * bptr, const char *units, char const * value)
{
    int u;
    if ((u = parseBytesUnits(units)) == 0) {
        self_destruct();
        return;
    }

    // Find number from string beginning.
    char const * number_begin = value;
    char const * number_end = value;

    while ((*number_end >= '0' && *number_end <= '9')) {
        ++number_end;
    }

    String number;
    number.limitInit(number_begin, number_end - number_begin);

    int d = xatoi(number.termedBuf());
    int m;
    if ((m = parseBytesUnits(number_end)) == 0) {
        self_destruct();
        return;
    }

    *bptr = static_cast<size_t>(m * d / u);
    if (static_cast<double>(*bptr) * 2 != (m * d / u) * 2)
        self_destruct();
}