static RegexList **
compileRE(RegexList **Tail, char * RE, int flags)
{
    int errcode;
    RegexList *q;
    regex_t comp;

    if (RE == NULL  ||  *RE == '\0')
        return Tail;

    if ((errcode = regcomp(&comp, RE, flags)) != 0) {
        char errbuf[256];
        regerror(errcode, &comp, errbuf, sizeof errbuf);
        debugs(28, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "ERROR: invalid regular expression: '" << RE << "': " << errbuf);
        return NULL;
    }
    debugs(28, 2, "compileRE: compiled '" << RE << "' with flags " << flags );

    q = (RegexList *) memAllocate(MEM_RELIST);
    q->pattern = xstrdup(RE);
    q->regex = comp;
    q->flags = flags;
    *(Tail) = q;
    Tail = &q->next;

    return Tail;
}