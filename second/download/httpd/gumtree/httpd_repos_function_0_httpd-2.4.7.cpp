static int checkmask(const char *data, const char *mask)
{
    int i, ch, d;

    for (i = 0; mask[i] != '\0' && mask[i] != '*'; i++) {
        ch = mask[i];
        d = data[i];
        if (ch == '@') {
            if (!isupper(d))
                return 0;
        }
        else if (ch == '$') {
            if (!islower(d))
                return 0;
        }
        else if (ch == '#') {
            if (!isdigit(d))
                return 0;
        }
        else if (ch == '&') {
            if (!isxdigit(d))
                return 0;
        }
        else if (ch != d)
            return 0;
    }

    if (mask[i] == '*')
        return 1;
    else
        return (data[i] == '\0');
}