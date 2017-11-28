static void
parse_access_log(customlog ** logs)
{
    const char *filename, *logdef_name;
    customlog *cl;
    logformat *lf;

    cl = (customlog *)xcalloc(1, sizeof(*cl));

    if ((filename = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }

    if (strcmp(filename, "none") == 0) {
        cl->type = CLF_NONE;
        aclParseAclList(LegacyParser, &cl->aclList);
        while (*logs)
            logs = &(*logs)->next;
        *logs = cl;
        return;
    }

    if ((logdef_name = strtok(NULL, w_space)) == NULL)
        logdef_name = "auto";

    debugs(3, 9, "Log definition name '" << logdef_name << "' file '" << filename << "'");

    cl->filename = xstrdup(filename);

    /* look for the definition pointer corresponding to this name */
    lf = Config.Log.logformats;

    while (lf != NULL) {
        debugs(3, 9, "Comparing against '" << lf->name << "'");

        if (strcmp(lf->name, logdef_name) == 0)
            break;

        lf = lf->next;
    }

    if (lf != NULL) {
        cl->type = CLF_CUSTOM;
        cl->logFormat = lf;
    } else if (strcmp(logdef_name, "auto") == 0) {
        cl->type = CLF_AUTO;
    } else if (strcmp(logdef_name, "squid") == 0) {
        cl->type = CLF_SQUID;
    } else if (strcmp(logdef_name, "common") == 0) {
        cl->type = CLF_COMMON;
#if ICAP_CLIENT
    } else if (strcmp(logdef_name, "icap_squid") == 0) {
        cl->type = CLF_ICAP_SQUID;
#endif
    } else {
        debugs(3, 0, "Log format '" << logdef_name << "' is not defined");
        self_destruct();
        return;
    }

    aclParseAclList(LegacyParser, &cl->aclList);

    while (*logs)
        logs = &(*logs)->next;

    *logs = cl;
}