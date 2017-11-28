void
aclParseRegexList(relist **curlist)
{
    relist **Tail;
    relist *q = NULL;
    char *t = NULL;
    regex_t comp;
    int errcode;
    int flags = REG_EXTENDED | REG_NOSUB;

    debugs(28,5, HERE << "Regex new line.");

    for (Tail = (relist **)curlist; *Tail; Tail = &((*Tail)->next));
    while ((t = ConfigParser::strtokFile())) {

        debugs(28,5, HERE << "Regex token: " << t);

        if (strcmp(t, "-i") == 0) {
            flags |= REG_ICASE;
            continue;
        }

        if (strcmp(t, "+i") == 0) {
            flags &= ~REG_ICASE;
            continue;
        }

        if ((errcode = regcomp(&comp, t, flags)) != 0) {
            char errbuf[256];
            regerror(errcode, &comp, errbuf, sizeof errbuf);
            debugs(28, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
            debugs(28, 0, "aclParseRegexList: Invalid regular expression '" << t << "': " << errbuf);
            continue;
        }

        q = (relist *)memAllocate(MEM_RELIST);
        q->flags = flags;
        q->pattern = xstrdup(t);
        q->regex = comp;
        *(Tail) = q;
        Tail = &q->next;
    }
}