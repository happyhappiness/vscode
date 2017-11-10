static const char *set_secure_upgradeable_listener(cmd_parms *cmd, void *dummy, 
                                       const char *ips, const char* key)
{
    NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
    seclistenup_rec *listen_node;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    char *ports, *addr;
    unsigned short port;
    seclistenup_rec *new;

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
    
    if (ports == ips) {
        addr = apr_pstrdup(cmd->pool, "0.0.0.0");
    }
    else {
        addr = apr_pstrdup(cmd->pool, ips);
    }

    port = atoi(ports);
    
    if (!port) 
	    return "Port must be numeric";

    apr_table_set(sc->slutable, ports, addr);

    new = apr_pcalloc(cmd->pool, sizeof(seclistenup_rec)); 
    new->next = ap_seclistenersup;
    strcpy(new->key, key);
    new->addr = addr;
    new->port = port;
    ap_seclistenersup = new;

    return err;
}