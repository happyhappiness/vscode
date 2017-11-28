static void
read_passwd_file(const char *passwordFile, int isHa1Mode)
{
    FILE *f;
    char buf[8192];
    user_data *u;
    char *user;
    char *passwd;
    char *ha1 = NULL;
    char *realm;

    if (hash != NULL) {
        hashFreeItems(hash, my_free);
    }
    /* initial setup */
    hash = hash_create((HASHCMP *) strcmp, 7921, hash_string);
    if (NULL == hash) {
        fprintf(stderr, "digest_pw_auth: cannot create hash table\n");
        exit(1);
    }
    f = fopen(passwordFile, "r");
    while (fgets(buf, 8192, f) != NULL) {
        if ((buf[0] == '#') || (buf[0] == ' ') || (buf[0] == '\t') ||
                (buf[0] == '\n'))
            continue;
        user = strtok(buf, ":\n");
        realm = strtok(NULL, ":\n");
        passwd = strtok(NULL, ":\n");
        if (!passwd) {
            passwd = realm;
            realm = NULL;
        }
        if ((strlen(user) > 0) && passwd) {
            if (strncmp(passwd, "{HHA1}", 6) == 0) {
                ha1 = passwd + 6;
                passwd = NULL;
            } else if (isHa1Mode) {
                ha1 = passwd;
                passwd = NULL;
            }
            if (ha1 && strlen(ha1) != 32) {
                /* We cannot accept plaintext passwords when using HA1 encoding,
                 * as the passwords may be output to cache.log if debugging is on.
                 */
                fprintf(stderr, "digest_pw_auth: ignoring invalid password for %s\n", user);
                continue;
            }
            u = xcalloc(1, sizeof(*u));
            if (realm) {
                int len = strlen(user) + strlen(realm) + 2;
                u->hash.key = malloc(len);
                snprintf(u->hash.key, len, "%s:%s", user, realm);
            } else {
                u->hash.key = xstrdup(user);
            }
            if (ha1)
                u->ha1 = xstrdup(ha1);
            else
                u->passwd = xstrdup(passwd);
            hash_join(hash, &u->hash);
        }
    }
    fclose(f);
}