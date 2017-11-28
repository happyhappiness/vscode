static int
ldap_escape_value(char *escaped, int size, const char *src)
{
    int n = 0;
    while (size > 4 && *src) {
        switch (*src) {
        case '*':
        case '(':
        case ')':
        case '\\':
            n += 3;
            size -= 3;
            if (size > 0) {
                *escaped = '\\';
                ++escaped;
                snprintf(escaped, 3, "%02x", (int) *src);
                ++src;
                escaped += 2;
            }
            break;
        default:
            *escaped = *src;
            ++escaped;
            ++src;
            ++n;
            --size;
        }
    }
    *escaped = '\0';
    return n;
}