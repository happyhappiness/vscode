int
main(int argc, char **argv)
{
    struct stat sb;
    time_t change_time = -1;
    char buf[256];
    char *user, *passwd, *p;
    user_data *u;
    setbuf(stdout, NULL);
    if (argc != 2) {
        fprintf(stderr, "Usage: ncsa_auth <passwordfile>\n");
        exit(1);
    }
    if (stat(argv[1], &sb) != 0) {
        fprintf(stderr, "cannot stat %s\n", argv[1]);
        exit(1);
    }
    while (fgets(buf, 256, stdin) != NULL) {
        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';		/* strip \n */
        if (stat(argv[1], &sb) == 0) {
            if (sb.st_mtime != change_time) {
                read_passwd_file(argv[1]);
                change_time = sb.st_mtime;
            }
        }
        if ((user = strtok(buf, " ")) == NULL) {
            printf("ERR\n");
            continue;
        }
        if ((passwd = strtok(NULL, "")) == NULL) {
            printf("ERR\n");
            continue;
        }
        rfc1738_unescape(user);
        rfc1738_unescape(passwd);
        u = (user_data *) hash_lookup(hash, user);
        if (u == NULL) {
            printf("ERR No such user\n");
#if HAVE_CRYPT
        } else if (strlen(passwd) <= 8 && strcmp(u->passwd, (char *) crypt(passwd, u->passwd)) == 0) {
            // Bug 3107: crypt() DES functionality silently truncates long passwords.
            printf("OK\n");
        } else if (strlen(passwd) > 8 && strcmp(u->passwd, (char *) crypt(passwd, u->passwd)) == 0) {
            // Bug 3107: crypt() DES functionality silently truncates long passwords.
            fprintf(stderr, "SECURITY ALERT: NCSA DES algorithm truncating user %s password to 8 bytes. Upgrade to MD5.", user);
            // Highly Unsafe: permit a transition period for admin to update passwords.
            printf("OK\n");
#endif
        } else if (strcmp(u->passwd, (char *) crypt_md5(passwd, u->passwd)) == 0) {
            printf("OK\n");
        } else if (strcmp(u->passwd, (char *) md5sum(passwd)) == 0) {
            printf("OK\n");
        } else {
            printf("ERR Wrong password\n");
        }
    }
    if (hash != NULL) {
        hashFreeItems(hash, my_free);
        hashFreeMemory(hash);
    }
    exit(0);
}