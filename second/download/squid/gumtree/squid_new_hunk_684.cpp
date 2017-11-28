            ++optind;
        if (opterr && *ostr != ':')
            (void) fprintf(stderr,
                           "%s: illegal option -- %c\n", __FILE__, optopt);
        return (BADCH);
    }
    if (*++oli != ':') {    /* don't need argument */
        optarg = NULL;
        if (!*place)
            ++optind;
    } else {            /* need an argument */
        if (*place)     /* no white space */
            optarg = place;
        else if (nargc <= ++optind) {	/* no arg */
            place = EMSG;
            if (*ostr == ':')
                return (BADARG);
            if (opterr)
                (void) fprintf(stderr,
                               "%s: option requires an argument -- %c\n",
                               __FILE__, optopt);
            return (BADCH);
        } else          /* white space */
            optarg = nargv[optind];
        place = EMSG;
        ++optind;
    }
    return (optopt);        /* dump back option letter */
}

