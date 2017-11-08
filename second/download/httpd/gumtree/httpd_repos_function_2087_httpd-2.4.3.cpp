static char *ycomp(sed_commands_t *commands, char *expbuf)
{
    char    c;
    int cint; /* integer value of char c */
    char *ep, *tsp;
    int i;
    char    *sp;

    ep = expbuf;
    if(ep + 0377 > &commands->respace[RESIZE-1]) {
        command_errf(commands, SEDERR_TMMES, commands->linebuf);
        return NULL;
    }
    sp = commands->cp;
    for(tsp = commands->cp; (c = *tsp) != commands->sseof; tsp++) {
        if(c == '\\')
            tsp++;
        if(c == '\0' || c == '\n') {
            command_errf(commands, SEDERR_EDMOSTR, commands->linebuf);
            return NULL;
        }
    }
    tsp++;
    memset(ep, 0, 0400);

    while((c = *sp++) != commands->sseof) {
        c &= 0377;
        if(c == '\\' && *sp == 'n') {
            sp++;
            c = '\n';
        }
        cint = (int) c;
        if((ep[cint] = *tsp++) == '\\' && *tsp == 'n') {
            ep[cint] = '\n';
            tsp++;
        }
        if(ep[cint] == commands->sseof || ep[cint] == '\0') {
            command_errf(commands, SEDERR_TSNTSS, commands->linebuf);
        }
    }
    if(*tsp != commands->sseof) {
        if(*tsp == '\0') {
            command_errf(commands, SEDERR_EDMOSTR, commands->linebuf);
        }
        else {
            command_errf(commands, SEDERR_TSNTSS, commands->linebuf);
        }
        return NULL;
    }
    commands->cp = ++tsp;

    for(i = 0; i < 0400; i++)
        if(ep[i] == 0)
            ep[i] = i;

    return(ep + 0400);
}