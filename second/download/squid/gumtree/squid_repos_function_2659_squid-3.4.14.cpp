pid_t
readPidFile(void)
{
    FILE *pid_fp = NULL;
    const char *f = Config.pidFilename;
    char *chroot_f = NULL;
    pid_t pid = -1;
    int i;

    if (f == NULL || !strcmp(Config.pidFilename, "none")) {
        fprintf(stderr, APP_SHORTNAME ": ERROR: No pid file name defined\n");
        exit(1);
    }

    if (Config.chroot_dir && geteuid() == 0) {
        int len = strlen(Config.chroot_dir) + 1 + strlen(f) + 1;
        chroot_f = (char *)xmalloc(strlen(Config.chroot_dir) + 1 + strlen(f) + 1);
        snprintf(chroot_f, len, "%s/%s", Config.chroot_dir, f);
        f = chroot_f;
    }

    pid_fp = fopen(f, "r");

    if (pid_fp != NULL) {
        pid = 0;

        if (fscanf(pid_fp, "%d", &i) == 1)
            pid = (pid_t) i;

        fclose(pid_fp);
    } else {
        if (errno != ENOENT) {
            fprintf(stderr, APP_SHORTNAME ": ERROR: Could not read pid file\n");
            fprintf(stderr, "\t%s: %s\n", f, xstrerror());
            exit(1);
        }
    }

    safe_free(chroot_f);
    return pid;
}