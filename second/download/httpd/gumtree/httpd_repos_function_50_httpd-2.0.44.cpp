static void clean_env(void)
{
    char pathbuf[512];
    char **cleanenv;
    char **ep;
    int cidx = 0;
    int idx;


    if ((cleanenv = (char **) calloc(AP_ENVBUF, sizeof(char *))) == NULL) {
        log_err("failed to malloc memory for environment\n");
        exit(120);
    }

    sprintf(pathbuf, "PATH=%s", AP_SAFE_PATH);
    cleanenv[cidx] = strdup(pathbuf);
    cidx++;

    for (ep = environ; *ep && cidx < AP_ENVBUF-1; ep++) {
        if (!strncmp(*ep, "HTTP_", 5) || !strncmp(*ep, "SSL_", 4)) {
            cleanenv[cidx] = *ep;
            cidx++;
        }
        else {
            for (idx = 0; safe_env_lst[idx]; idx++) {
                if (!strncmp(*ep, safe_env_lst[idx],
                             strlen(safe_env_lst[idx]))) {
                    cleanenv[cidx] = *ep;
                    cidx++;
                    break;
                }
            }
        }
    }

    cleanenv[cidx] = NULL;

    environ = cleanenv;
}