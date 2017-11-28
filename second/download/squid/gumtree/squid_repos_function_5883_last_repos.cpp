static void
read_passwd_file(const char *passwdfile)
{
    FILE *f;
    char buf[HELPER_INPUT_BUFFER];
    char *user;
    char *passwd;

    usermap.clear();
    //TODO: change to c++ streams
    f = fopen(passwdfile, "r");
    if (!f) {
        int xerrno = errno;
        fprintf(stderr, "FATAL: %s: %s\n", passwdfile, xstrerr(xerrno));
        exit(1);
    }
    unsigned int lineCount = 0;
    buf[HELPER_INPUT_BUFFER-1] = '\0';
    while (fgets(buf, sizeof(buf)-1, f) != NULL) {
        ++lineCount;
        if ((buf[0] == '#') || (buf[0] == ' ') || (buf[0] == '\t') ||
                (buf[0] == '\n'))
            continue;
        user = strtok(buf, ":\n\r");
        if (user == NULL) {
            fprintf(stderr, "ERROR: Missing user name at %s line %d\n", passwdfile, lineCount);
            continue;
        }
        passwd = strtok(NULL, ":\n\r");
        if ((strlen(user) > 0) && passwd) {
            usermap[user] = passwd;
        }
    }
    fclose(f);
}