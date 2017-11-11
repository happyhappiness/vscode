static const char *set_secure_listener(cmd_parms *cmd, void *dummy,
                                       const char *ips, const char* key,
                                       const char* mutual)
{
    NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    char *ports, *addr;
    unsigned short port;
    seclisten_rec *new;
    ap_listen_rec **walk;
    apr_sockaddr_t *sa;
    int found_listener = 0;


    if (err != NULL)
        return err;

    ports = strchr(ips, ':');

    if (ports != NULL) {
        if (ports == ips)
            return "Missing IP address";
        else if (ports[1] == '\0')
            return "Address must end in :<port-number>";

        *(ports++) = '\0';
    }
    else {
        ports = (char*)ips;
    }

    new = apr_pcalloc(cmd->server->process->pool, sizeof(seclisten_rec));
    new->local_addr.sin_family = AF_INET;

    if (ports == ips) {
        new->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr = apr_pstrdup(cmd->server->process->pool, "0.0.0.0");
    }
    else {
        new->local_addr.sin_addr.s_addr = parse_addr(ips, NULL);
        addr = apr_pstrdup(cmd->server->process->pool, ips);
    }

    port = atoi(ports);

    if (!port)
        return "Port must be numeric";

    /* If the specified addr:port was created previously, put the listen
       socket record back on the ap_listeners list so that the socket
       will be reused rather than recreated */
    for (walk = &nw_old_listeners; *walk;) {
        sa = (*walk)->bind_addr;
        if (sa) {
            ap_listen_rec *new;
            apr_port_t oldport;

            oldport = sa->port;
            /* If both ports are equivalent, then if their names are equivalent,
             * then we will re-use the existing record.
             */
            if (port == oldport &&
                ((!addr && !sa->hostname) ||
                 ((addr && sa->hostname) && !strcmp(sa->hostname, addr)))) {
                new = *walk;
                *walk = new->next;
                new->next = ap_listeners;
                ap_listeners = new;
                found_listener = 1;
                continue;
            }
        }

        walk = &(*walk)->next;
    }

    apr_table_add(sc->sltable, ports, addr);

    /* If we found a pre-existing listen socket record, then there
       is no need to create a new secure listen socket record. */
    if (found_listener) {
        return NULL;
    }

    new->local_addr.sin_port = htons(port);
    new->fd = -1;
    new->used = 0;
    new->next = ap_seclisteners;
    strcpy(new->key, key);
    new->mutual = (mutual) ? 1 : 0;
    new->addr = addr;
    new->port = port;
    ap_seclisteners = new;
    return NULL;
}