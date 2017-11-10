static void normalise(unsigned int flags, char *str)
{
    char *p;
    if (flags & NORM_LC)
        for (p = str; *p; ++p)
            if (isupper(*p))
                *p = tolower(*p);

    if (flags & NORM_MSSLASH)
        for (p = ap_strchr(str, '\\'); p; p = ap_strchr(p+1, '\\'))
            *p = '/';

}