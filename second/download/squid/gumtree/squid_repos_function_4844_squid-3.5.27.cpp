const char *
ACLFlags::flagsStr() const
{
    static char buf[64];
    if (flags_ == 0)
        return "";

    char *s = buf;
    *s++ = '-';
    for (ACLFlag f = 'A'; f <= 'z'; f++) {
        // ACL_F_REGEX_CASE (-i) flag handled by ACLRegexData class, ignore
        if (isSet(f) && f != ACL_F_REGEX_CASE)
            *s++ = f;
    }
    *s = '\0';
    return buf;
}