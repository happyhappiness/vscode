static void
read_passwd_file(const char *passwdfile)
{
    FILE *f;
    char buf[HELPER_INPUT_BUFFER];
    user_data *u;
    char *user;
    char *passwd;
    if (hash != NULL) {
        hashFreeItems(hash, my_free);
        hashFreeMemory(hash);
    }
    /* initial setup */
    hash = hash_create((HASHCMP *) strcmp, 7921, hash_string);
    if (NULL == hash) {
        fprintf(stderr, "FATAL: Cannot create hash table\n");
        exit(1);
    }
    f = fopen(passwdfile, "r");
    if (NULL == f) {
        fprintf(stderr, "FATAL: %s: %s\n", passwdfile, xstrerror());
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
            u = static_cast<user_data*>(xmalloc(sizeof(*u)));
            u->user = xstrdup(user);
            u->passwd = xstrdup(passwd);
            hash_join(hash, (hash_link *) u);
        }
    }
    fclose(f);
}