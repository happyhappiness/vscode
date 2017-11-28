void
strwordquote(MemBuf * mb, const char *str)
{
    int quoted = 0;

    if (strchr(str, ' ')) {
        quoted = 1;
        mb->append("\"", 1);
    }

    while (*str) {
        int l = strcspn(str, "\"\\\n\r");
        mb->append(str, l);
        str += l;

        switch (*str) {

        case '\n':
            mb->append("\\n", 2);
            str++;
            break;

        case '\r':
            mb->append("\\r", 2);
            str++;
            break;

        case '\0':
            break;

        default:
            mb->append("\\", 1);
            mb->append(str, 1);
            str++;
            break;
        }
    }

    if (quoted)
        mb->append("\"", 1);
}