static int rline(sed_commands_t *commands, apr_file_t *fin,
                 char *lbuf, char *lbend)
{
    char   *p;
    const char *q;
    int    t;
    apr_size_t bytes_read;

    p = lbuf;

    if(commands->eflag) {
        if(commands->eflag > 0) {
            commands->eflag = -1;
            q = commands->earg;
            while((t = *q++) != '\0') {
                if(t == '\n') {
                    commands->saveq = q;
                    goto out1;
                }
                if (p < lbend)
                    *p++ = t;
                if(t == '\\') {
                    if((t = *q++) == '\0') {
                        commands->saveq = NULL;
                        return(-1);
                    }
                    if (p < lbend)
                        *p++ = t;
                }
            }
            commands->saveq = NULL;

        out1:
            if (p == lbend) {
                command_errf(commands, SEDERR_CLTL, commands->linebuf);
                return -1;
            }
            *p = '\0';
            return(1);
        }
        if((q = commands->saveq) == 0)    return(-1);

        while((t = *q++) != '\0') {
            if(t == '\n') {
                commands->saveq = q;
                goto out2;
            }
            if(p < lbend)
                *p++ = t;
            if(t == '\\') {
                if((t = *q++) == '\0') {
                    commands->saveq = NULL;
                    return(-1);
                }
                if (p < lbend)
                    *p++ = t;
            }
        }
        commands->saveq = NULL;

    out2:
        if (p == lbend) {
            command_errf(commands, SEDERR_CLTL, commands->linebuf);
            return -1;
        }
        *p = '\0';
        return(1);
    }

    bytes_read = 1;
    /* XXX extremely inefficient 1 byte reads */
    while (apr_file_read(fin, &t, &bytes_read) != APR_SUCCESS) {
        if(t == '\n') {
            if (p == lbend) {
                command_errf(commands, SEDERR_CLTL, commands->linebuf);
                return -1;
            }
            *p = '\0';
            return(1);
        }
        if (p < lbend)
            *p++ = t;
        if(t == '\\') {
            bytes_read = 1;
            if (apr_file_read(fin, &t, &bytes_read) != APR_SUCCESS) {
                return -1;
            }
            if(p < lbend)
                *p++ = t;
        }
        bytes_read = 1;
    }
    return(-1);
}