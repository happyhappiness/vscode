static const char *get_default_charset(void)
{
#ifdef __MVS__
#    ifdef __CODESET__
        return __CODESET__;
#    else
        return "IBM-1047";
#    endif
#endif

    if ('}' == 0xD0) {
        return "IBM-1047";
    }

    if ('{' == 0xFB) {
        return "EDF04";
    }

    if ('A' == 0xC1) {
        return "EBCDIC"; /* not useful */
    }

    if ('A' == 0x41) {
        return "ISO8859-1"; /* not necessarily true */
    }

    return "unknown";
}