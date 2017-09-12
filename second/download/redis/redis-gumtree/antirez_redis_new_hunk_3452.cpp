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
