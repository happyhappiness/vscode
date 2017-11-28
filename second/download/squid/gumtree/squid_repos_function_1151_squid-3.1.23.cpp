static void
parse_logformat(logformat ** logformat_definitions)
{
    logformat *nlf;
    char *name, *def;

    if ((name = strtok(NULL, w_space)) == NULL)
        self_destruct();

    if ((def = strtok(NULL, "\r\n")) == NULL) {
        self_destruct();
        return;
    }

    debugs(3, 2, "Logformat for '" << name << "' is '" << def << "'");

    nlf = (logformat *)xcalloc(1, sizeof(logformat));

    nlf->name = xstrdup(name);

    if (!accessLogParseLogFormat(&nlf->format, def)) {
        self_destruct();
        return;
    }

    nlf->next = *logformat_definitions;

    *logformat_definitions = nlf;
}