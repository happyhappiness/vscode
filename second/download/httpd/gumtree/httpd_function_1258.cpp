static apr_status_t htdbm_make(htdbm_t *htdbm)
{
    char cpw[MAX_STRING_LEN];
    char salt[9];

    switch (htdbm->alg) {
        case ALG_APSHA:
            /* XXX cpw >= 28 + strlen(sha1) chars - fixed len SHA */
            apr_sha1_base64(htdbm->userpass,strlen(htdbm->userpass),cpw);
        break;

        case ALG_APMD5:
            (void) srand((int) time((time_t *) NULL));
            to64(&salt[0], rand(), 8);
            salt[8] = '\0';
            apr_md5_encode((const char *)htdbm->userpass, (const char *)salt,
                            cpw, sizeof(cpw));
        break;
        case ALG_PLAIN:
            /* XXX this len limitation is not in sync with any HTTPd len. */
            apr_cpystrn(cpw,htdbm->userpass,sizeof(cpw));
#if APR_HAVE_CRYPT_H
            fprintf(stderr, "Warning: Plain text passwords aren't supported by the "
                    "server on this platform!\n");
#endif
        break;
#if APR_HAVE_CRYPT_H
        case ALG_CRYPT:
            (void) srand((int) time((time_t *) NULL));
            to64(&salt[0], rand(), 8);
            salt[8] = '\0';
            apr_cpystrn(cpw, (char *)crypt(htdbm->userpass, salt), sizeof(cpw) - 1);
            fprintf(stderr, "CRYPT is now deprecated, use MD5 instead!\n");
#endif
        default:
        break;
    }
    htdbm->userpass = apr_pstrdup(htdbm->pool, cpw);
    return APR_SUCCESS;
}