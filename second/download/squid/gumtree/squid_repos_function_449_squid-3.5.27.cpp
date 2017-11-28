int
main(int argc, char **argv)
{
    int auth = 0;
    char buf[HELPER_INPUT_BUFFER];
    char *user, *passwd, *p;

    setbuf(stdout, NULL);
    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {

        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';      /* strip \n */

        if ((user = strtok(buf, " ")) == NULL) {
            SEND_ERR("No Username");
            continue;
        }
        if ((passwd = strtok(NULL, "")) == NULL) {
            SEND_ERR("No Password");
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
            SEND_ERR("No such user");
        } else {
            if (auth == 2) {
                SEND_ERR("Wrong password");
            } else {
                SEND_OK("");
            }
        }
    }
    return 0;
}