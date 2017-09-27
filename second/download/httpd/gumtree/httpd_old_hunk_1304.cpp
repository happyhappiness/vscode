
    case ALG_PLAIN:
        /* XXX this len limitation is not in sync with any HTTPd len. */
        apr_cpystrn(cpw,pw,sizeof(cpw));
        break;

#if !(defined(WIN32) || defined(NETWARE))
    case ALG_CRYPT:
    default:
        if (seed_rand()) {
            break;
        }
        to64(&salt[0], rand(), 8);
        salt[8] = '\0';

        apr_cpystrn(cpw, (char *)crypt(pw, salt), sizeof(cpw) - 1);
        break;
#endif
    }
    memset(pw, '\0', strlen(pw));

    /*
