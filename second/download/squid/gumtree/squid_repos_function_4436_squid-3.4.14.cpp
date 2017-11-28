static bool parseBytesOptionValue(size_t * bptr, char const * value)
{
    // Find number from string beginning.
    char const * number_begin = value;
    char const * number_end = value;

    while ((*number_end >= '0' && *number_end <= '9')) {
        ++number_end;
    }

    std::string number(number_begin, number_end - number_begin);
    std::istringstream in(number);
    int d = 0;
    if (!(in >> d))
        return false;

    int m;
    if ((m = parseBytesUnits(number_end)) == 0) {
        return false;
    }

    *bptr = static_cast<size_t>(m * d);
    if (static_cast<long>(*bptr * 2) != m * d * 2)
        return false;

    return true;
}