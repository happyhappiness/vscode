static char *select_random_value_part(request_rec *r, char *value)
{
    char *p = value;
    unsigned n = 1;

    /* count number of distinct values */
    while ((p = ap_strchr(p, '|')) != NULL) {
        ++n;
        ++p;
    }

    if (n > 1) {
        /* initialize random generator
         *
         * XXX: Probably this should be wrapped into a thread mutex,
         * shouldn't it? Is it worth the effort?
         */
        if (!rewrite_rand_init_done) {
            srand((unsigned)(getpid()));
            rewrite_rand_init_done = 1;
        }

        /* select a random subvalue */
        n = (int)(((double)(rand() % RAND_MAX) / RAND_MAX) * n + 1);

        /* extract it from the whole string */
        while (--n && (value = ap_strchr(value, '|')) != NULL) {
            ++value;
        }

        if (value) { /* should not be NULL, but ... */
            p = ap_strchr(value, '|');
            if (p) {
                *p = '\0';
            }
        }
    }

    return value;
}