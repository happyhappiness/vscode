static void
shellUnescape(char *buf)
{
    if (!buf)
        return;

    unsigned char *p, *d;

    d = p = reinterpret_cast<unsigned char *>(buf);

    while (auto ch = *p) {

        if (ch == '\\') {
            ++p;

            switch (*p) {
            case 'n':
                ch = '\n';
                break;
            case 'r':
                ch = '\r';
                break;
            case 't':
                ch = '\t';
                break;
            case '\\':
                ch = '\\';
                break;
            default:
                ch = *p;
                debugVerbose(1, "Warning: unsupported shell code '\\" << ch << "'");
                break;
            }

            *d = ch;

            if (!ch)
                continue;

        } else {
            *d = *p;
        }

        ++p;
        ++d;
    }

    *d = '\0';
}