long
Ssl::parse_options(const char *options)
{
    long op = 0;
    char *tmp;
    char *option;

    if (!options)
        goto no_options;

    tmp = xstrdup(options);

    option = strtok(tmp, ":,");

    while (option) {

        struct ssl_option *opt = NULL, *opttmp;
        long value = 0;
        enum {
            MODE_ADD, MODE_REMOVE
        } mode;

        switch (*option) {

        case '!':

        case '-':
            mode = MODE_REMOVE;
            ++option;
            break;

        case '+':
            mode = MODE_ADD;
            ++option;
            break;

        default:
            mode = MODE_ADD;
            break;
        }

        for (opttmp = ssl_options; opttmp->name; ++opttmp) {
            if (strcmp(opttmp->name, option) == 0) {
                opt = opttmp;
                break;
            }
        }

        if (opt)
            value = opt->value;
        else if (strncmp(option, "0x", 2) == 0) {
            /* Special case.. hex specification */
            value = strtol(option + 2, NULL, 16);
        } else {
            fatalf("Unknown SSL option '%s'", option);
            value = 0;		/* Keep GCC happy */
        }

        switch (mode) {

        case MODE_ADD:
            op |= value;
            break;

        case MODE_REMOVE:
            op &= ~value;
            break;
        }

        option = strtok(NULL, ":,");
    }

    safe_free(tmp);

no_options:
    return op;
}