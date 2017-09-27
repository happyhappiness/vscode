        break;
#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
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
