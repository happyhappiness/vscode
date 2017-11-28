static void
log_quoted_string(const char *str, char *out)
{
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
            *p = '\\';
            ++p;
            *p = 'r';
            ++p;
            ++str;
            break;

        case '\n':
            *p = '\\';
            ++p;
            *p = 'n';
            ++p;
            ++str;
            break;

        case '\t':
            *p = '\\';
            ++p;
            *p = 't';
            ++p;
            ++str;
            break;

        default:
            *p = '\\';
            ++p;
            *p = *str;
            ++p;
            ++str;
            break;
        }
    }

    *p = '\0';
}