            fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
            return 1;
    }
    if (!strcasecmp(rc->name,"monitor")) read_forever = 1;
    if ((fd = cliConnect()) == -1) return 1;

    /* Select db number */
