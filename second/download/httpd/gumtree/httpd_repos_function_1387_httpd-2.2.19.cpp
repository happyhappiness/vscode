static int parse_byterange(char *range, apr_off_t clength,
                           apr_off_t *start, apr_off_t *end)
{
    char *dash = strchr(range, '-');
    char *errp;
    apr_off_t number;

    if (!dash) {
        return 0;
    }

    if ((dash == range)) {
        /* In the form "-5" */
        if (apr_strtoff(&number, dash+1, &errp, 10) || *errp) {
            return 0;
        }
        *start = clength - number;
        *end = clength - 1;
    }
    else {
        *dash++ = '\0';
        if (apr_strtoff(&number, range, &errp, 10) || *errp) {
            return 0;
        }
        *start = number;
        if (*dash) {
            if (apr_strtoff(&number, dash, &errp, 10) || *errp) {
                return 0;
            }
            *end = number;
        }
        else {                  /* "5-" */
            *end = clength - 1;
        }
    }

    if (*start < 0) {
        *start = 0;
    }

    if (*end >= clength) {
        *end = clength - 1;
    }

    if (*start > *end) {
        return -1;
    }

    return (*start > 0 || *end < clength);
}