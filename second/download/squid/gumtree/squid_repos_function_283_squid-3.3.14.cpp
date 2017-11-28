int
get_ldap_hostname_list(struct main_args *margs, struct hstruct **hlist, int nh, char *domain)
{

    /*
     * char name[sysconf(_SC_HOST_NAME_MAX)];
     */
    char name[1024];
    char host[NS_MAXDNAME];
    char *service = NULL;
    struct hstruct *hp = NULL;
    struct lsstruct *ls = NULL;
    int nhosts = 0;
    int size;
    int type, rdlength;
    int priority, weight, port;
    int len, olen;
    int i, j, k;
    u_char *buffer = NULL;
    u_char *p;

    ls = margs->lservs;
    while (ls) {
        debug((char *) "%s| %s: DEBUG: Ldap server loop: lserver@domain %s@%s\n", LogTime(), PROGRAM, ls->lserver, ls->domain?ls->domain:"NULL");
        if (ls->domain && !strcasecmp(ls->domain, domain)) {
            debug((char *) "%s| %s: DEBUG: Found lserver@domain %s@%s\n", LogTime(), PROGRAM, ls->lserver, ls->domain);
            hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nhosts + 1));
            hp[nhosts].host = strdup(ls->lserver);
            hp[nhosts].port = -1;
            hp[nhosts].priority = -2;
            hp[nhosts].weight = -2;
            ++nhosts;
        } else if ( !ls->domain || !strcasecmp(ls->domain, "") ) {
            debug((char *) "%s| %s: DEBUG: Found lserver@domain %s@%s\n", LogTime(), PROGRAM, ls->lserver, ls->domain?ls->domain:"NULL");
            hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nhosts + 1));
            hp[nhosts].host = strdup(ls->lserver);
            hp[nhosts].port = -1;
            hp[nhosts].priority = -2;
            hp[nhosts].weight = -2;
            ++nhosts;

        }
        ls = ls->next;
    }
    /* found ldap servers in predefined list -> exit */
    if (nhosts > 0)
        goto cleanup;

    if (margs->ssl) {
        service = (char *) xmalloc(strlen("_ldaps._tcp.") + strlen(domain) + 1);
        strcpy(service, "_ldaps._tcp.");
    } else {
        service = (char *) xmalloc(strlen("_ldap._tcp.") + strlen(domain) + 1);
        strcpy(service, "_ldap._tcp.");
    }
    strcat(service, domain);

#ifndef PACKETSZ_MULT
    /*
     * It seems Solaris doesn't give back the real length back when res_search uses a to small buffer
     * Set a bigger one here
     */
#define PACKETSZ_MULT 10
#endif

    hp = *hlist;
    buffer = (u_char *) xmalloc(PACKETSZ_MULT * NS_PACKETSZ);
    if ((len = res_search(service, ns_c_in, ns_t_srv, (u_char *) buffer, PACKETSZ_MULT * NS_PACKETSZ)) < 0) {
        error((char *) "%s| %s: ERROR: Error while resolving service record %s with res_search\n", LogTime(), PROGRAM, service);
        nsError(h_errno, service);
        if (margs->ssl) {
            xfree(service);
            service = (char *) xmalloc(strlen("_ldap._tcp.") + strlen(domain) + 1);
            strcpy(service, "_ldap._tcp.");
            strcat(service, domain);
            if ((len = res_search(service, ns_c_in, ns_t_srv, (u_char *) buffer, PACKETSZ_MULT * NS_PACKETSZ)) < 0) {
                error((char *) "%s| %s: ERROR: Error while resolving service record %s with res_search\n", LogTime(), PROGRAM, service);
                nsError(h_errno, service);
                goto finalise;
            }
        } else {
            goto finalise;
        }
    }
    if (len > PACKETSZ_MULT * NS_PACKETSZ) {
        olen = len;
        buffer = (u_char *) xrealloc(buffer, len);
        if ((len = res_search(service, ns_c_in, ns_t_srv, (u_char *) buffer, len)) < 0) {
            error((char *) "%s| %s: ERROR: Error while resolving service record %s with res_search\n", LogTime(), PROGRAM, service);
            nsError(h_errno, service);
            goto finalise;
        }
        if (len > olen) {
            error((char *) "%s| %s: ERROR: Reply to big: buffer: %d reply length: %d\n", LogTime(), PROGRAM, olen, len);
            goto finalise;
        }
    }
    p = buffer;
    p += 6 * NS_INT16SZ;	/* Header(6*16bit) = id + flags + 4*section count */
    if (p > buffer + len) {
        error((char *) "%s| %s: ERROR: Message to small: %d < header size\n", LogTime(), PROGRAM, len);
        goto finalise;
    }
    if ((size = dn_expand(buffer, buffer + len, p, name, sysconf(_SC_HOST_NAME_MAX))) < 0) {
        error((char *) "%s| %s: ERROR: Error while expanding query name with dn_expand:  %s\n", LogTime(), PROGRAM, strerror(errno));
        goto finalise;
    }
    p += size;			/* Query name */
    p += 2 * NS_INT16SZ;	/* Query type + class (2*16bit) */
    if (p > buffer + len) {
        error((char *) "%s| %s: ERROR: Message to small: %d < header + query name,type,class \n", LogTime(), PROGRAM, len);
        goto finalise;
    }
    while (p < buffer + len) {
        if ((size = dn_expand(buffer, buffer + len, p, name, sysconf(_SC_HOST_NAME_MAX))) < 0) {
            error((char *) "%s| %s: ERROR: Error while expanding answer name with dn_expand:  %s\n", LogTime(), PROGRAM, strerror(errno));
            goto finalise;
        }
        p += size;		/* Resource Record name */
        if (p > buffer + len) {
            error((char *) "%s| %s: ERROR: Message to small: %d < header + query name,type,class + answer name\n", LogTime(), PROGRAM, len);
            goto finalise;
        }
        NS_GET16(type, p);	/* RR type (16bit) */
        p += NS_INT16SZ + NS_INT32SZ;	/* RR class + ttl (16bit+32bit) */
        if (p > buffer + len) {
            error((char *) "%s| %s: ERROR: Message to small: %d < header + query name,type,class + answer name + RR type,class,ttl\n", LogTime(), PROGRAM, len);
            goto finalise;
        }
        NS_GET16(rdlength, p);	/* RR data length (16bit) */

        if (type == ns_t_srv) {	/* SRV record */
            if (p > buffer + len) {
                error((char *) "%s| %s: ERROR: Message to small: %d < header + query name,type,class + answer name + RR type,class,ttl + RR data length\n", LogTime(), PROGRAM, len);
                goto finalise;
            }
            NS_GET16(priority, p);	/* Priority (16bit) */
            if (p > buffer + len) {
                error((char *) "%s| %s: ERROR: Message to small: %d <  SRV RR + priority\n", LogTime(), PROGRAM, len);
                goto finalise;
            }
            NS_GET16(weight, p);	/* Weight (16bit) */
            if (p > buffer + len) {
                error((char *) "%s| %s: ERROR: Message to small: %d <  SRV RR + priority + weight\n", LogTime(), PROGRAM, len);
                goto finalise;
            }
            NS_GET16(port, p);	/* Port (16bit) */
            if (p > buffer + len) {
                error((char *) "%s| %s: ERROR: Message to small: %d <  SRV RR + priority + weight + port\n", LogTime(), PROGRAM, len);
                goto finalise;
            }
            if ((size = dn_expand(buffer, buffer + len, p, host, NS_MAXDNAME)) < 0) {
                error((char *) "%s| %s: ERROR: Error while expanding SRV RR name with dn_expand:  %s\n", LogTime(), PROGRAM, strerror(errno));
                goto finalise;
            }
            debug((char *) "%s| %s: DEBUG: Resolved SRV %s record to %s\n", LogTime(), PROGRAM, service, host);
            hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nh + 1));
            hp[nh].host = xstrdup(host);
            hp[nh].port = port;
            hp[nh].priority = priority;
            hp[nh].weight = weight;
            ++nh;
            p += size;
        } else {
            p += rdlength;
        }
        if (p > buffer + len) {
            error((char *) "%s| %s: ERROR: Message to small: %d <  SRV RR + priority + weight + port + name\n", LogTime(), PROGRAM, len);
            goto finalise;
        }
    }
    if (p != buffer + len) {
#if (SIZEOF_LONG == 8)
        error("%s| %s: ERROR: Inconsistence message length: %ld!=0\n", LogTime(), PROGRAM, buffer + len - p);
#else
        error((char *) "%s| %s: ERROR: Inconsistence message length: %d!=0\n", LogTime(), PROGRAM, buffer + len - p);
#endif
        goto finalise;
    }

finalise:
    nhosts = get_hostname_list(margs, &hp, nh, domain);

    debug("%s| %s: DEBUG: Adding %s to list\n", LogTime(), PROGRAM, domain);

    hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nhosts + 1));
    hp[nhosts].host = strdup(domain);
    hp[nhosts].port = -1;
    hp[nhosts].priority = -2;
    hp[nhosts].weight = -2;
    ++nhosts;

cleanup:
    /* Remove duplicates */
    for (i = 0; i < nhosts; ++i) {
        for (j = i + 1; j < nhosts; ++j) {
            if (!strcasecmp(hp[i].host, hp[j].host)) {
                if (hp[i].port == hp[j].port ||
                        (hp[i].port == -1 && hp[j].port == 389) ||
                        (hp[i].port == 389 && hp[j].port == -1)) {
                    xfree(hp[j].host);
                    for (k = j + 1; k < nhosts; ++k) {
                        hp[k - 1].host = hp[k].host;
                        hp[k - 1].port = hp[k].port;
                        hp[k - 1].priority = hp[k].priority;
                        hp[k - 1].weight = hp[k].weight;
                    }
                    --j;
                    --nhosts;
                    hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nhosts + 1));
                }
            }
        }
    }

    /* Sort by Priority / Weight */
    msort(hp, nhosts, compare_hosts);

    if (debug_enabled) {
        debug((char *) "%s| %s: DEBUG: Sorted ldap server names for domain %s:\n", LogTime(), PROGRAM, domain);
        for (i = 0; i < nhosts; ++i) {
            debug((char *) "%s| %s: DEBUG: Host: %s Port: %d Priority: %d Weight: %d\n", LogTime(), PROGRAM, hp[i].host, hp[i].port, hp[i].priority, hp[i].weight);
        }
    }
    if (buffer)
        xfree(buffer);
    if (service)
        xfree(service);
    *hlist = hp;
    return (nhosts);
}