static APR_INLINE int fnmatch_ch(const char **pattern, const char **string, int flags)
{
    const char * const mismatch = *pattern;
    const int nocase = !!(flags & APR_FNM_CASE_BLIND);
    const int escape = !(flags & APR_FNM_NOESCAPE);
    const int slash = !!(flags & APR_FNM_PATHNAME);
    int result = APR_FNM_NOMATCH;
    const char *startch;
    int negate;

    if (**pattern == '[')
    {
        ++*pattern;

        /* Handle negation, either leading ! or ^ operators (never both) */
        negate = ((**pattern == '!') || (**pattern == '^'));
        if (negate)
            ++*pattern;

        /* ']' is an ordinary character at the start of the range pattern */
        if (**pattern == ']')
            goto leadingclosebrace;

        while (**pattern)
        {
            if (**pattern == ']') {
                ++*pattern;
                /* XXX: Fix for MBCS character width */
                ++*string;
                return (result ^ negate);
            }

            if (escape && (**pattern == '\\')) {
                ++*pattern;

                /* Patterns must be terminated with ']', not EOS */
                if (!**pattern)
                    break;
            }

            /* Patterns must be terminated with ']' not '/' */
            if (slash && (**pattern == '/'))
                break;

leadingclosebrace:
            /* Look at only well-formed range patterns; 
             * "x-]" is not allowed unless escaped ("x-\]")
             * XXX: Fix for locale/MBCS character width
             */
            if (((*pattern)[1] == '-') && ((*pattern)[2] != ']'))
            {
                startch = *pattern;
                *pattern += (escape && ((*pattern)[2] == '\\')) ? 3 : 2;

                /* NOT a properly balanced [expr] pattern, EOS terminated 
                 * or ranges containing a slash in FNM_PATHNAME mode pattern
                 * fall out to to the rewind and test '[' literal code path
                 */
                if (!**pattern || (slash && (**pattern == '/')))
                    break;

                /* XXX: handle locale/MBCS comparison, advance by MBCS char width */
                if ((**string >= *startch) && (**string <= **pattern))
                    result = 0;
                else if (nocase && (isupper(**string) || isupper(*startch)
                                                      || isupper(**pattern))
                            && (tolower(**string) >= tolower(*startch)) 
                            && (tolower(**string) <= tolower(**pattern)))
                    result = 0;

                ++*pattern;
                continue;
            }

            /* XXX: handle locale/MBCS comparison, advance by MBCS char width */
            if ((**string == **pattern))
                result = 0;
            else if (nocase && (isupper(**string) || isupper(**pattern))
                            && (tolower(**string) == tolower(**pattern)))
                result = 0;

            ++*pattern;
        }

        /* NOT a properly balanced [expr] pattern; Rewind
         * and reset result to test '[' literal
         */
        *pattern = mismatch;
        result = APR_FNM_NOMATCH;
    }
    else if (**pattern == '?') {
        /* Optimize '?' match before unescaping **pattern */
        if (!**string || (slash && (**string == '/')))
            return APR_FNM_NOMATCH;
        result = 0;
        goto fnmatch_ch_success;
    }
    else if (escape && (**pattern == '\\') && (*pattern)[1]) {
        ++*pattern;
    }

    /* XXX: handle locale/MBCS comparison, advance by the MBCS char width */
    if (**string == **pattern)
        result = 0;
    else if (nocase && (isupper(**string) || isupper(**pattern))
                    && (tolower(**string) == tolower(**pattern)))
        result = 0;

    /* Refuse to advance over trailing slash or nulls
     */
    if (!**string || !**pattern || (slash && ((**string == '/') || (**pattern == '/'))))
        return result;

fnmatch_ch_success:
    ++*pattern;
    ++*string;
    return result;
}