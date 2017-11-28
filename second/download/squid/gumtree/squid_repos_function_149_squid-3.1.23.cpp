static int
build_filter(char *filter, int size, const char *template, const char *user, const char *group)
{
    int n;
    while (*template && size > 0) {
        switch (*template) {
        case '%':
            template++;
            switch (*template) {
            case 'u':
            case 'v':
                template++;
                n = ldap_escape_value(filter, size, user);
                size -= n;
                filter += n;
                break;
            case 'g':
            case 'a':
                template++;
                n = ldap_escape_value(filter, size, group);
                size -= n;
                filter += n;
                break;
            default:
                fprintf(stderr, "ERROR: Unknown filter template string %%%c\n", *template);
                return 1;
                break;
            }
            break;
        case '\\':
            template++;
            if (*template) {
                *filter++ = *template++;
                size--;
            }
            break;
        default:
            *filter++ = *template++;
            size--;
            break;
        }
    }
    if (size <= 0) {
        fprintf(stderr, "ERROR: Filter too large\n");
        return 1;
    }
    *filter = '\0';
    return 0;
}