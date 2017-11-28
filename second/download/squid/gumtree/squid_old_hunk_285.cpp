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

void
dumpMallocStats(void)
{
#if HAVE_MSTATS && HAVE_GNUMALLOC_H
