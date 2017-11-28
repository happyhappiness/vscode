int
main(int argc, char *argv[])
{
    int i;
    char buf[HELPER_INPUT_BUFFER];
    struct SMBDOMAIN *dom;
    char *s;
    char *user;
    char *pass;
    char *domname;
    FILE *p;
    const char *shcmd;

    /* make standard output line buffered */
    if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
        return 1;

    /* parse command line arguments */
    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-d") == 0) {
            debug_enabled = 1;
            continue;
        }
        /* the next options require an argument */
        if (i + 1 == argc)
            break;

        if (strcmp(argv[i], "-W") == 0) {
            dom = static_cast<struct SMBDOMAIN *>(xmalloc(sizeof(struct SMBDOMAIN)));

            dom->name = dom->sname = argv[++i];
            dom->passthrough = "";
            dom->nmbaddr = "";
            dom->nmbcast = NMB_BROADCAST;
            dom->authshare = (char *)"NETLOGON";
            dom->authfile = "proxyauth";
            dom->next = NULL;

            /* append to linked list */
            if (lastdom != NULL)
                lastdom->next = dom;
            else
                firstdom = dom;

            lastdom = dom;
            continue;
        }
        if (strcmp(argv[i], "-w") == 0) {
            if (lastdom != NULL)
                lastdom->sname = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-P") == 0) {
            if (lastdom != NULL)
                lastdom->passthrough = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-B") == 0) {
            if (lastdom != NULL) {
                lastdom->nmbaddr = argv[++i];
                lastdom->nmbcast = NMB_BROADCAST;
            }
            continue;
        }
        if (strcmp(argv[i], "-U") == 0) {
            if (lastdom != NULL) {
                lastdom->nmbaddr = argv[++i];
                lastdom->nmbcast = NMB_UNICAST;
            }
            continue;
        }
        if (strcmp(argv[i], "-S") == 0) {
            if (lastdom != NULL) {
                if ((lastdom->authshare = xstrdup(argv[++i])) == NULL)
                    return 1;

                /* convert backslashes to forward slashes */
                for (s = lastdom->authshare; *s != '\0'; ++s)
                    if (*s == '\\')
                        *s = '/';

                /* strip leading forward slash from share name */
                if (*lastdom->authshare == '/')
                    ++lastdom->authshare;

                if ((s = strchr(lastdom->authshare, '/')) != NULL) {
                    *s = '\0';
                    lastdom->authfile = s + 1;
                }
            }
            continue;
        }
    }

    shcmd = debug_enabled ? HELPERSCRIPT : HELPERSCRIPT " > /dev/null 2>&1";

    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {

        if ((s = strchr(buf, '\n')) == NULL)
            continue;
        *s = '\0';

        if ((s = strchr(buf, ' ')) == NULL) {
            SEND_ERR("");
            continue;
        }
        *s = '\0';

        user = buf;
        pass = s + 1;
        domname = NULL;

        rfc1738_unescape(user);
        rfc1738_unescape(pass);

        if ((s = strchr(user, '\\')) != NULL) {
            *s = '\0';
            domname = user;
            user = s + 1;
        }
        /* match domname with linked list */
        if (domname != NULL && strlen(domname) > 0) {
            for (dom = firstdom; dom != NULL; dom = dom->next)
                if (strcasecmp(dom->sname, domname) == 0)
                    break;
        } else
            dom = firstdom;

        if (dom == NULL) {
            SEND_ERR("");
            continue;
        }
        if ((p = popen(shcmd, "w")) == NULL) {
            SEND_ERR("");
            continue;
        }
        (void) fprintf(p, "%s\n", dom->name);
        (void) fprintf(p, "%s\n", dom->passthrough);
        (void) fprintf(p, "%s\n", dom->nmbaddr);
        (void) fprintf(p, "%d\n", dom->nmbcast);
        (void) fprintf(p, "%s\n", dom->authshare);
        (void) fprintf(p, "%s\n", dom->authfile);
        (void) fprintf(p, "%s\n", user);
        /* the password can contain special characters */
        print_esc(p, pass);
        (void) fputc('\n', p);
        (void) fflush(p);

        if (pclose(p) == 0)
            SEND_OK("");
        else
            SEND_ERR("");
    }               /* while (1) */
    return 0;
}