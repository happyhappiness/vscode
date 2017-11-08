static const char *non_regex_pattern(apr_pool_t *p, const char *s)
{
    const char *src = s;
    int escapes_found = 0;
    int in_escape = 0;

    while (*src) {
        if (in_escape) {
            in_escape = 0;
        }
        else {
            switch (*src) {
            case '^':
            case '.':
            case '$':
            case '|':
            case '(':
            case ')':
            case '[':
            case ']':
            case '*':
            case '+':
            case '?':
            case '{':
            case '}':
                return NULL;
            case '\\':
                in_escape = 1;
                escapes_found = 1;
            }
        }
        src++;
    }
    if (!escapes_found) {
        return s;
    }
    else {
        char *unescaped = (char *)apr_palloc(p, src - s + 1);
        char *dst = unescaped;
        src = s;
        do {
            if (*src == '\\') {
                src++;
            }
        } while ((*dst++ = *src++));
        return unescaped;
    }
}