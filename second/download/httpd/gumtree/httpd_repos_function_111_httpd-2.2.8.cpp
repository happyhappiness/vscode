static int mkrecord(char *user, char *record, apr_size_t rlen, char *passwd,
                    int alg)
{
    char *pw;
    char cpw[120];
    char pwin[MAX_STRING_LEN];
    char pwv[MAX_STRING_LEN];
    char salt[9];
    apr_size_t bufsize;

    if (passwd != NULL) {
        pw = passwd;
    }
    else {
        bufsize = sizeof(pwin);
        if (apr_password_get("New password: ", pwin, &bufsize) != 0) {
            apr_snprintf(record, (rlen - 1), "password too long (>%"
                         APR_SIZE_T_FMT ")", sizeof(pwin) - 1);
            return ERR_OVERFLOW;
        }
        bufsize = sizeof(pwv);
        apr_password_get("Re-type new password: ", pwv, &bufsize);
        if (strcmp(pwin, pwv) != 0) {
            apr_cpystrn(record, "password verification error", (rlen - 1));
            return ERR_PWMISMATCH;
        }
        pw = pwin;
        memset(pwv, '\0', sizeof(pwin));
    }
    switch (alg) {

    case ALG_APSHA:
        /* XXX cpw >= 28 + strlen(sha1) chars - fixed len SHA */
        apr_sha1_base64(pw,strlen(pw),cpw);
        break;

    case ALG_APMD5:
        (void) srand((int) time((time_t *) NULL));
        to64(&salt[0], rand(), 8);
        salt[8] = '\0';

        apr_md5_encode((const char *)pw, (const char *)salt,
                     cpw, sizeof(cpw));
        break;

    case ALG_PLAIN:
        /* XXX this len limitation is not in sync with any HTTPd len. */
        apr_cpystrn(cpw,pw,sizeof(cpw));
        break;

#if !(defined(WIN32) || defined(NETWARE))
    case ALG_CRYPT:
    default:
        (void) srand((int) time((time_t *) NULL));
        to64(&salt[0], rand(), 8);
        salt[8] = '\0';

        apr_cpystrn(cpw, (char *)crypt(pw, salt), sizeof(cpw) - 1);
        break;
#endif
    }
    memset(pw, '\0', strlen(pw));

    /*
     * Check to see if the buffer is large enough to hold the username,
     * hash, and delimiters.
     */
    if ((strlen(user) + 1 + strlen(cpw)) > (rlen - 1)) {
        apr_cpystrn(record, "resultant record too long", (rlen - 1));
        return ERR_OVERFLOW;
    }
    strcpy(record, user);
    strcat(record, ":");
    strcat(record, cpw);
    strcat(record, "\n");
    return 0;
}