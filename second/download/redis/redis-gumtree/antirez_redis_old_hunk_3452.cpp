            switch(c[1]) {
            case 's':
                arg = va_arg(ap,char*);
                current = sdscat(current,arg);
                break;
            case 'b':
                arg = va_arg(ap,char*);
                size = va_arg(ap,size_t);
                current = sdscatlen(current,arg,size);
                break;
            case '%':
                cmd = sdscat(cmd,"%");
                break;
            }
            c++;
        }
        c++;
    }

    /* Add the last argument if needed */
    if (sdslen(current) != 0) {
        addArgument(current, &argv, &argc, &totlen);
    } else {
        sdsfree(current);
