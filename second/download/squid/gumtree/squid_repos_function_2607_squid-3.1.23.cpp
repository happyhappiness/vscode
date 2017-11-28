static void
mail_warranty(void)
{
    FILE *fp = NULL;
    static char command[256];
#if HAVE_MKSTEMP

    char filename[] = "/tmp/squid-XXXXXX";
    int tfd = mkstemp(filename);

    if (tfd < 0)
        return;

    if ((fp = fdopen(tfd, "w")) == NULL)
        return;

#else

    char *filename;

    if ((filename = tempnam(NULL, APP_SHORTNAME)) == NULL)
        return;

    if ((fp = fopen(filename, "w")) == NULL)
        return;

#endif

    if (Config.EmailFrom)
        fprintf(fp, "From: %s\n", Config.EmailFrom);
    else
        fprintf(fp, "From: %s@%s\n", APP_SHORTNAME, uniqueHostname());

    fprintf(fp, "To: %s\n", Config.adminEmail);

    fprintf(fp, "Subject: %s\n", dead_msg());

    fclose(fp);

    snprintf(command, 256, "%s %s < %s", Config.EmailProgram, Config.adminEmail, filename);

    if (system(command)) {}		/* XXX should avoid system(3) */

    unlink(filename);
}