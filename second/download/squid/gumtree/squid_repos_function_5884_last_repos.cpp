int
main(int argc, char **argv)
{
    struct stat sb;
    time_t change_time = -1;
    char buf[HELPER_INPUT_BUFFER];
    char *user, *passwd, *p;
    setbuf(stdout, NULL);
    if (argc != 2) {
        fprintf(stderr, "Usage: ncsa_auth <passwordfile>\n");
        exit(1);
    }
    if (stat(argv[1], &sb) != 0) {
        fprintf(stderr, "FATAL: cannot stat %s\n", argv[1]);
        exit(1);
    }
    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {
        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';      /* strip \n */
        if (stat(argv[1], &sb) == 0) {
            if (sb.st_mtime != change_time) {
                read_passwd_file(argv[1]);
                change_time = sb.st_mtime;
            }
        }
        if ((user = strtok(buf, " ")) == NULL) {
            SEND_ERR("");
            continue;
        }
        if ((passwd = strtok(NULL, "")) == NULL) {
            SEND_ERR("");
            continue;
        }
        rfc1738_unescape(user);
        rfc1738_unescape(passwd);
        const auto userpassIterator = usermap.find(user);
        if (userpassIterator == usermap.end()) {
            SEND_ERR("No such user");
            continue;
        }
        std::string stored_pass = userpassIterator->second;
        const char *salted = stored_pass.c_str(); // locally stored version contains salt etc.

        char *crypted = NULL;
#if HAVE_CRYPT
        size_t passwordLength = strlen(passwd);
        // Bug 3831: given algorithms more secure than DES crypt() does not truncate, so we can ignore the bug 3107 length checks below
        // '$1$' = MD5, '$2a$' = Blowfish, '$5$' = SHA256 (Linux), '$6$' = SHA256 (BSD) and SHA512
        if (passwordLength > 1 && salted[0] == '$' &&
                (crypted = crypt(passwd, salted)) && stored_pass == crypted) {
            SEND_OK("");
            continue;
        }
        // 'other' prefixes indicate DES algorithm.
        if (passwordLength <= 8 && (crypted = crypt(passwd, salted)) && stored_pass == crypted) {
            SEND_OK("");
            continue;
        }
        if (passwordLength > 8 && (crypted = crypt(passwd, salted)) && stored_pass == crypted) {
            // Bug 3107: crypt() DES functionality silently truncates long passwords.
            SEND_ERR("Password too long. Only 8 characters accepted.");
            continue;
        }

#endif
        if ( (crypted = crypt_md5(passwd, salted)) && stored_pass == crypted) {
            SEND_OK("");
            continue;
        }
        if ( (crypted = md5sum(passwd)) && stored_pass == crypted) {
            SEND_OK("");
            continue;
        }
        SEND_ERR("Wrong password");
    }
    exit(0);
}