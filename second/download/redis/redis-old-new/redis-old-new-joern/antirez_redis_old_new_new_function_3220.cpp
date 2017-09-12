int redisvFormatCommand(char **target, const char *format, va_list ap) {
    size_t size;
    const char *arg, *c = format;
    char *cmd = NULL; /* final command */
    int pos; /* position in final command */
    sds current; /* current argument */
    int interpolated = 0; /* did we do interpolation on an argument? */
    char **argv = NULL;
    int argc = 0, j;
    int totlen = 0;

    /* Abort if there is not target to set */
    if (target == NULL)
        return -1;

    /* Build the command string accordingly to protocol */
    current = sdsempty();
    while(*c != '\0') {
        if (*c != '%' || c[1] == '\0') {
            if (*c == ' ') {
                if (sdslen(current) != 0) {
                    addArgument(current, &argv, &argc, &totlen);
                    current = sdsempty();
                    interpolated = 0;
                }
            } else {
                current = sdscatlen(current,c,1);
            }
        } else {
            switch(c[1]) {
            case 's':
                arg = va_arg(ap,char*);
                size = strlen(arg);
                if (size > 0)
                    current = sdscatlen(current,arg,size);
                interpolated = 1;
                break;
            case 'b':
                arg = va_arg(ap,char*);
                size = va_arg(ap,size_t);
                if (size > 0)
                    current = sdscatlen(current,arg,size);
                interpolated = 1;
                break;
            case '%':
                current = sdscat(current,"%");
                break;
            default:
                /* Try to detect printf format */
                {
                    char _format[16];
                    const char *_p = c+1;
                    size_t _l = 0;
                    va_list _cpy;

                    /* Flags */
                    if (*_p != '\0' && *_p == '#') _p++;
                    if (*_p != '\0' && *_p == '0') _p++;
                    if (*_p != '\0' && *_p == '-') _p++;
                    if (*_p != '\0' && *_p == ' ') _p++;
                    if (*_p != '\0' && *_p == '+') _p++;

                    /* Field width */
                    while (*_p != '\0' && isdigit(*_p)) _p++;

                    /* Precision */
                    if (*_p == '.') {
                        _p++;
                        while (*_p != '\0' && isdigit(*_p)) _p++;
                    }

                    /* Modifiers */
                    if (*_p != '\0') {
                        if (*_p == 'h' || *_p == 'l') {
                            /* Allow a single repetition for these modifiers */
                            if (_p[0] == _p[1]) _p++;
                            _p++;
                        }
                    }

                    /* Conversion specifier */
                    if (*_p != '\0' && strchr("diouxXeEfFgGaA",*_p) != NULL) {
                        _l = (_p+1)-c;
                        if (_l < sizeof(_format)-2) {
                            memcpy(_format,c,_l);
                            _format[_l] = '\0';
                            va_copy(_cpy,ap);
                            current = sdscatvprintf(current,_format,_cpy);
                            interpolated = 1;
                            va_end(_cpy);

                            /* Update current position (note: outer blocks
                             * increment c twice so compensate here) */
                            c = _p-1;
                        }
                    }

                    /* Consume and discard vararg */
                    va_arg(ap,void);
                }
            }
            c++;
        }
        c++;
    }

    /* Add the last argument if needed */
    if (interpolated || sdslen(current) != 0) {
        addArgument(current, &argv, &argc, &totlen);
    } else {
        sdsfree(current);
    }

    /* Add bytes needed to hold multi bulk count */
    totlen += 1+intlen(argc)+2;

    /* Build the command at protocol level */
    cmd = malloc(totlen+1);
    if (!cmd) redisOOM();
    pos = sprintf(cmd,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
        pos += sprintf(cmd+pos,"$%zu\r\n",sdslen(argv[j]));
        memcpy(cmd+pos,argv[j],sdslen(argv[j]));
        pos += sdslen(argv[j]);
        sdsfree(argv[j]);
        cmd[pos++] = '\r';
        cmd[pos++] = '\n';
    }
    assert(pos == totlen);
    free(argv);
    cmd[totlen] = '\0';
    *target = cmd;
    return totlen;
}