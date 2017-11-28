static int
rad_auth_config(const char *cfname)
{
    FILE *cf;
    char line[MAXLINE];
    int srv = 0, crt = 0;

    if ((cf = fopen(cfname, "r")) == NULL) {
        perror(cfname);
        return -1;
    }
    while (fgets(line, MAXLINE, cf) != NULL) {
        if (!memcmp(line, "server", 6))
            srv = sscanf(line, "server %s", server);
        if (!memcmp(line, "secret", 6))
            crt = sscanf(line, "secret %s", secretkey);
        if (!memcmp(line, "identifier", 10))
            sscanf(line, "identifier %s", identifier);
        if (!memcmp(line, "service", 7))
            sscanf(line, "service %s", svc_name);
        if (!memcmp(line, "port", 4))
            sscanf(line, "port %s", svc_name);
        if (!memcmp(line, "timeout", 7))
            sscanf(line, "timeout %d", &retries);
    }
    fclose(cf);
    if (srv && crt)
        return 0;
    return -1;
}