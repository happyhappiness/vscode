int main(int argc, char *argv[])
{
    int i;
    int result;
    gid_t gid;
    struct group *grent;
    struct group fake_grent;

    /*
     * Assume success. :-)
     */
    result = 0;
    for (i = 1; i < argc; ++i) {
        char *arg;
        arg = argv[i];

        /*
         * If it's from a 'Group #-1' statement, get the numeric value
         * and skip the group lookup stuff.
         */
        if (*arg == '#') {
            gid = atoi(&arg[1]);
            fake_grent.gr_gid = gid;
            grent = &fake_grent;
        }
        else {
            grent = getgrnam(arg);
        }

        /*
         * A NULL return means no such group was found, so we're done
         * with this one.
         */
        if (grent == NULL) {
            fprintf(stderr, "%s: group '%s' not found\n", argv[0], arg);
            result = -1;
        }
        else {
            int check;

            /*
             * See if we can switch to the numeric GID we have. If so,
             * all well and good; if not, well..
             */
            gid = grent->gr_gid;
            check = setgid(gid);
            if (check != 0) {
                fprintf(stderr, "%s: invalid group '%s'\n", argv[0], arg);
                perror(argv[0]);
                result = -1;
            }
        }
    }
    /*
     * Worst-case return value.
     */
    return result;
}