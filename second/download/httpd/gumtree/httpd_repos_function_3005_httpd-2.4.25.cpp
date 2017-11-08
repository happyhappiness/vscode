static char *text(sed_commands_t *commands, char *textbuf, char *tbend)
{
    char   *p, *q;

    p = textbuf;
    q = commands->cp;
#ifndef S5EMUL
    /*
     * Strip off indentation from text to be inserted.
     */
    while(*q == '\t' || *q == ' ')    q++;
#endif
    for(;;) {

        if(p > tbend)
            return(NULL);    /* overflowed the buffer */
        if((*p = *q++) == '\\')
            *p = *q++;
        if(*p == '\0') {
            commands->cp = --q;
            return(++p);
        }
#ifndef S5EMUL
        /*
         * Strip off indentation from text to be inserted.
         */
        if(*p == '\n') {
            while(*q == '\t' || *q == ' ')    q++;
        }
#endif
        p++;
    }
}