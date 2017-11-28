static void
read_passwd_file(const char *passwdfile)
{
    FILE *f;
    char buf[8192];
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
        fprintf(stderr, "ncsa_auth: cannot create hash table\n");
        exit(1);
    }
    f = fopen(passwdfile, "r");
    if (NULL == f) {
        fprintf(stderr, "%s: %s\n", passwdfile, xstrerror());
        exit(1);
    }
    while (fgets(buf, 8192, f) != NULL) {
        if ((buf[0] == '#') || (buf[0] == ' ') || (buf[0] == '\t') ||
                (buf[0] == '\n'))
            continue;
        user = strtok(buf, ":\n\r");
        passwd = strtok(NULL, ":\n\r");
        if ((strlen(user) > 0) && passwd) {
            u = xmalloc(sizeof(*u));
            u->user = xstrdup(user);
            u->passwd = xstrdup(passwd);
            hash_join(hash, (hash_link *) u);
        }
    }
    fclose(f);
}