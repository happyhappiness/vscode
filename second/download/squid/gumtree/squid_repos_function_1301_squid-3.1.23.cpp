char *
strwordtok(char *buf, char **t)
{
    unsigned char *word = NULL;
    unsigned char *p = (unsigned char *) buf;
    unsigned char *d;
    unsigned char ch;
    int quoted = 0;

    if (!p)
        p = (unsigned char *) *t;

    if (!p)
        goto error;

    while (*p && xisspace(*p))
        p++;

    if (!*p)
        goto error;

    word = d = p;

    while ((ch = *p)) {
        switch (ch) {

        case '\\':
            p++;

            switch (*p) {

            case 'n':
                ch = '\n';

                break;

            case 'r':
                ch = '\r';

                break;

            default:
                ch = *p;

                break;

            }

            *d++ = ch;

            if (ch)
                p++;

            break;

        case '"':
            quoted = !quoted;

            p++;

            break;

        default:
            if (!quoted && xisspace(*p)) {
                p++;
                goto done;
            }

            *d++ = *p++;
            break;
        }
    }

done:
    *d++ = '\0';

error:
    *t = (char *) p;
    return (char *) word;
}