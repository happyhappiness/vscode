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
