static char *address(sed_commands_t *commands, char *expbuf,
                     apr_status_t* status)
{
    char   *rcp;
    apr_int64_t lno;
    sed_comp_args compargs;

    *status = APR_SUCCESS;
    if(*commands->cp == '$') {
        if (expbuf > &commands->respace[RESIZE-2]) {
            command_errf(commands, SEDERR_TMMES, commands->linebuf);
            *status = APR_EGENERAL;
            return NULL;
        }
        commands->cp++;
        *expbuf++ = CEND;
        *expbuf++ = CCEOF;
        return(expbuf);
    }
    if (*commands->cp == '/' || *commands->cp == '\\' ) {
        if ( *commands->cp == '\\' )
            commands->cp++;
        commands->sseof = *commands->cp++;
        return(comple(commands, &compargs, (char *) 0, expbuf, commands->reend,
                      commands->sseof));
    }

    rcp = commands->cp;
    lno = 0;

    while(*rcp >= '0' && *rcp <= '9')
        lno = lno*10 + *rcp++ - '0';

    if(rcp > commands->cp) {
        if (expbuf > &commands->respace[RESIZE-3]) {
            command_errf(commands, SEDERR_TMMES, commands->linebuf);
            *status = APR_EGENERAL;
            return NULL;
        }
        *expbuf++ = CLNUM;
        *expbuf++ = commands->nlno;
        commands->tlno[commands->nlno++] = lno;
        if(commands->nlno >= SED_NLINES) {
            command_errf(commands, SEDERR_TMLNMES);
            *status = APR_EGENERAL;
            return NULL;
        }
        *expbuf++ = CCEOF;
        commands->cp = rcp;
        return(expbuf);
    }
    return(NULL);
}