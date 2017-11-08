static char *compsub(sed_commands_t *commands,
                     sed_comp_args *compargs, char *rhsbuf)
{
    char   *p, *q;

    p = rhsbuf;
    q = commands->cp;
    for(;;) {
        if(p > &commands->respace[RESIZE-1]) {
            command_errf(commands, SEDERR_TMMES, commands->linebuf);
            return NULL;
        }
        if((*p = *q++) == '\\') {
            p++;
            if(p > &commands->respace[RESIZE-1]) {
                command_errf(commands, SEDERR_TMMES, commands->linebuf);
                return NULL;
            }
            *p = *q++;
            if(*p > compargs->nbra + '0' && *p <= '9') {
                command_errf(commands, SEDERR_DOORNG, commands->linebuf);
                return NULL;
            }
            p++;
            continue;
        }
        if(*p == commands->sseof) {
            *p++ = '\0';
            commands->cp = q;
            return(p);
        }
          if(*p++ == '\0') {
            command_errf(commands, SEDERR_EDMOSUB, commands->linebuf);
            return NULL;
        }
    }
}