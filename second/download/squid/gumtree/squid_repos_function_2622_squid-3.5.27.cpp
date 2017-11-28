static void
mail_warranty(void)
{
    FILE *fp = NULL;
    static char command[256];

    /*
     * NP: umask() takes the mask of bits we DONT want set.
     *
     * We want the current user to have read/write access
     * and since this file will be passed to mailsystem,
     * the group and other must have read access.
     */
    const mode_t prev_umask=umask(S_IXUSR|S_IXGRP|S_IWGRP|S_IWOTH|S_IXOTH);

#if HAVE_MKSTEMP
    char filename[] = "/tmp/squid-XXXXXX";
    int tfd = mkstemp(filename);
    if (tfd < 0 || (fp = fdopen(tfd, "w")) == NULL) {
        umask(prev_umask);
        return;
    }
#else
    char *filename;
    // XXX tempnam is obsolete since POSIX.2008-1
    // tmpfile is not an option, we want the created files to stick around
    if ((filename = tempnam(NULL, APP_SHORTNAME)) == NULL ||
            (fp = fopen(filename, "w")) == NULL) {
        umask(prev_umask);
        return;
    }
#endif
    umask(prev_umask);

    if (Config.EmailFrom)
        fprintf(fp, "From: %s\n", Config.EmailFrom);
    else
        fprintf(fp, "From: %s@%s\n", APP_SHORTNAME, uniqueHostname());

    fprintf(fp, "To: %s\n", Config.adminEmail);
    fprintf(fp, "Subject: %s\n", dead_msg());
    fclose(fp);

    snprintf(command, 256, "%s %s < %s", Config.EmailProgram, Config.adminEmail, filename);
    if (system(command)) {}     /* XXX should avoid system(3) */
    unlink(filename);
#if !HAVE_MKSTEMP
    xfree(filename); // tempnam() requires us to free its allocation
#endif
}