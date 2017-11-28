int
main(int argc, char **argv)
{
    int auth = 0;
    char buf[256];
    char *user, *passwd, *p;

    setbuf(stdout, NULL);
    while (fgets(buf, 256, stdin) != NULL) {

        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';		/* strip \n */

        if ((user = strtok(buf, " ")) == NULL) {
            printf(ERR);
            continue;
        }
        if ((passwd = strtok(NULL, "")) == NULL) {
            printf(ERR);
            continue;
        }
        rfc1738_unescape(user);
        rfc1738_unescape(passwd);
#if HAVE_SHADOW_H
        auth = shadow_auth(user, passwd);
#else
        auth = passwd_auth(user, passwd);
#endif
        if (auth == 0) {
            printf("ERR No such user\n");
        } else {
            if (auth == 2) {
                printf("ERR Wrong password\n");
            } else {
                printf(OK);
            }
        }
    }
    exit(0);
}