static void cgethost (struct in_addr ipnum, char *string, int check)
{
    struct nsrec **current, *new;
    struct hostent *hostdata;
    char *name;

    current = &nscache[((ipnum.s_addr + (ipnum.s_addr >> 8) +
                         (ipnum.s_addr >> 16) + (ipnum.s_addr >> 24)) % BUCKETS)];

    while (*current != NULL && ipnum.s_addr != (*current)->ipnum.s_addr)
        current = &(*current)->next;

    if (*current == NULL) {
        cachesize++;
        new = (struct nsrec *) malloc(sizeof(struct nsrec));
        if (new == NULL) {
            perror("malloc");
            fprintf(stderr, "Insufficient memory\n");
            exit(1);
        }
        *current = new;
        new->next = NULL;

        new->ipnum = ipnum;

        hostdata = gethostbyaddr((const char *) &ipnum, sizeof(struct in_addr),
                                 AF_INET);
        if (hostdata == NULL) {
            if (h_errno > MAX_ERR)
                errors[UNKNOWN_ERR]++;
            else
                errors[h_errno]++;
            new->noname = h_errno;
            name = strdup(inet_ntoa(ipnum));
        }
        else {
            new->noname = 0;
            name = strdup(hostdata->h_name);
            if (check) {
                if (name == NULL) {
                    perror("strdup");
                    fprintf(stderr, "Insufficient memory\n");
                    exit(1);
                }
                hostdata = gethostbyname(name);
                if (hostdata != NULL) {
                    char **hptr;

                    for (hptr = hostdata->h_addr_list; *hptr != NULL; hptr++)
                        if (((struct in_addr *) (*hptr))->s_addr == ipnum.s_addr)
                            break;
                    if (*hptr == NULL)
                        hostdata = NULL;
                }
                if (hostdata == NULL) {
                    fprintf(stderr, "Bad host: %s != %s\n", name,
                            inet_ntoa(ipnum));
                    new->noname = NO_REVERSE;
                    free(name);
                    name = strdup(inet_ntoa(ipnum));
                    errors[NO_REVERSE]++;
                }
            }
        }
        new->hostname = name;
        if (new->hostname == NULL) {
            perror("strdup");
            fprintf(stderr, "Insufficient memory\n");
            exit(1);
        }
    }
    else
        cachehits++;

    /* size of string == MAXDNAME +1 */
    strncpy(string, (*current)->hostname, MAXDNAME);
    string[MAXDNAME] = '\0';
}