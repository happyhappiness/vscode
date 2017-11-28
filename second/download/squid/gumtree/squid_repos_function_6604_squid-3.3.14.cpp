int
getopt(nargc, nargv, ostr)
int nargc;
char *const *nargv;
const char *ostr;
{
    static char *place = EMSG;	/* option letter processing */
    char *oli;			/* option letter list index */

    if (optreset || !*place) {	/* update scanning pointer */
        optreset = 0;
        if (optind >= nargc || *(place = nargv[optind]) != '-') {
            place = EMSG;
            return (-1);
        }
        if (place[1] && *++place == '-') {	/* found "--" */
            ++optind;
            place = EMSG;
            return (-1);
        }
    }				/* option letter okay? */
    if ((optopt = (int) *place++) == (int) ':' ||
            !(oli = strchr(ostr, optopt))) {
        /*
         * if the user didn't specify '-' as an option,
         * assume it means -1.
         */
        if (optopt == (int) '-')
            return (-1);
        if (!*place)
            ++optind;
        if (opterr && *ostr != ':')
            (void) fprintf(stderr,
                           "%s: illegal option -- %c\n", __FILE__, optopt);
        return (BADCH);
    }
    if (*++oli != ':') {	/* don't need argument */
        optarg = NULL;
        if (!*place)
            ++optind;
    } else {			/* need an argument */
        if (*place)		/* no white space */
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
        } else			/* white space */
            optarg = nargv[optind];
        place = EMSG;
        ++optind;
    }
    return (optopt);		/* dump back option letter */
}