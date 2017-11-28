static size_t parseBytesUnits(const char * unit)
{
    if (!strncasecmp(unit, B_BYTES_STR, strlen(B_BYTES_STR)) ||
            !strncasecmp(unit, "", strlen(unit)))
        return 1;

    if (!strncasecmp(unit, B_KBYTES_STR, strlen(B_KBYTES_STR)))
        return 1 << 10;

    if (!strncasecmp(unit, B_MBYTES_STR, strlen(B_MBYTES_STR)))
        return 1 << 20;

    if (!strncasecmp(unit, B_GBYTES_STR, strlen(B_GBYTES_STR)))
        return 1 << 30;

    std::cerr << "WARNING: Unknown bytes unit '" << unit << "'" << std::endl;

    return 0;
}