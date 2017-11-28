static char *
log_quoted_string(const char *str)
{
    char *out = (char *)xmalloc(strlen(str) * 2 + 1);
    char *p = out;

    while (*str) {
        int l = strcspn(str, "\"\\\r\n\t");
        memcpy(p, str, l);
        str += l;
        p += l;

        switch (*str) {

        case '\0':
            break;

        case '\r':
            *p++ = '\\';
            *p++ = 'r';
            str++;
            break;

        case '\n':
            *p++ = '\\';
            *p++ = 'n';
            str++;
            break;

        case '\t':
            *p++ = '\\';
            *p++ = 't';
            str++;
            break;

        default:
            *p++ = '\\';
            *p++ = *str;
            str++;
            break;
        }
    }

    *p++ = '\0';
    return out;
}