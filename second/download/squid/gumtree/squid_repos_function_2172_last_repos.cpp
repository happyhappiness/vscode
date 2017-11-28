char *
ConfigParser::UnQuote(const char *token, const char **next)
{
    const char *errorStr = NULL;
    const char *errorPos = NULL;
    char quoteChar = *token;
    assert(quoteChar == '"' || quoteChar == '\'');
    LOCAL_ARRAY(char, UnQuoted, CONFIG_LINE_LIMIT);
    const char  *s = token + 1;
    char *d = UnQuoted;
    /* scan until the end of the quoted string, handling escape sequences*/
    while (*s && *s != quoteChar && !errorStr && (size_t)(d - UnQuoted) < sizeof(UnQuoted)) {
        if (*s == '\\') {
            s++;
            switch (*s) {
            case 'r':
                *d = '\r';
                break;
            case 'n':
                *d = '\n';
                break;
            case 't':
                *d = '\t';
                break;
            default:
                if (isalnum(*s)) {
                    errorStr = "Unsupported escape sequence";
                    errorPos = s;
                }
                *d = *s;
                break;
            }
#if 0
        } else if (*s == '$' && quoteChar == '"') {
            errorStr = "Unsupported cfg macro";
            errorPos = s;
#endif
#if 0
        } else if (*s == '%' && quoteChar == '"' && (!AllowMacros_ )) {
            errorStr = "Macros are not supported here";
            errorPos = s;
#endif
        } else
            *d = *s;
        ++s;
        ++d;
    }

    if (*s != quoteChar && !errorStr) {
        errorStr = "missing quote char at the end of quoted string";
        errorPos = s - 1;
    }
    // The end of token
    *d = '\0';

    // We are expecting a separator after quoted string, space or one of "()#"
    if (*(s + 1) != '\0' && !strchr(w_space "()#", *(s + 1)) && !errorStr) {
        errorStr = "Expecting space after the end of quoted token";
        errorPos = token;
    }

    if (errorStr) {
        if (PreviewMode_)
            xstrncpy(UnQuoted, SQUID_ERROR_TOKEN, sizeof(UnQuoted));
        else {
            debugs(3, DBG_CRITICAL, "FATAL: " << errorStr << ": " << errorPos);
            self_destruct();
        }
    }

    if (next)
        *next = s + 1;
    return UnQuoted;
}