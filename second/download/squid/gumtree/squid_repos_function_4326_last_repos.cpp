static void
InitConf()
{
    *(edui_conf.program) = '\0';
    *(edui_conf.basedn) = '\0';
    *(edui_conf.host) = '\0';
    *(edui_conf.attrib) = '\0';
    *(edui_conf.dn) = '\0';
    *(edui_conf.passwd) = '\0';
    *(edui_conf.search_filter) = '\0';
    edui_conf.scope = -1;
    edui_conf.ver = -1;
    edui_conf.port = -1;
    edui_conf.persist_timeout = -1;
    edui_conf.mode = 0;
    edui_conf.mode |= EDUI_MODE_INIT;

    /* Set defaults from compile-time-options, if provided, but depriciated. */
#ifdef EDUI_BASE_DN
    xstrncpy(edui_conf.basedn, EDUI_BASE_DN, sizeof(edui_conf.basedn));
#endif
#ifdef EDUI_DEFAULT_HOST
    xstrncpy(edui_conf.host, EDUI_DEFAULT_HOST, sizeof(edui_conf.host));
#endif
#ifdef EDUI_BIND_DN
    xstrncpy(edui_conf.dn, EDUI_BIND_DN, sizeof(edui_conf.dn));
#endif
#ifdef EDUI_BIND_PASS
    xstrncpy(edui_conf.passwd, EDUI_BIND_PASS, sizeof(edui_conf.passwd));
#endif
#ifdef EDUI_USER_ATTRIB
    xstrncpy(edui_conf.attrib, EDUI_USER_ATTRIB, sizeof(edui_conf.attrib));
#endif
#ifdef EDUI_SEARCH_FILTER
    xstrncpy(edui_conf.search_filter, EDUI_SEARCH_FILTER, sizeof(edui_conf.search_filter));
#endif
#ifdef EDUI_SEARCH_SCOPE
    if (!strcmp(EDUI_SEARCH_SCOPE, "base"))
        edui_conf.scope = 0;
    else if (!strcmp(EDUI_SEARCH_SCOPE, "one"))
        edui_conf.scope = 1;
    else if (!strcmp(EDUI_SEARCH_SCOPE, "sub"))
        edui_conf.scope = 2;
    else
        edui_conf.scope = 1;
#endif
#ifdef EDUI_LDAP_VERSION
    edui_conf.ver = EDUI_LDAP_VERSION;
#endif
#ifdef EDUI_DEFAULT_PORT
    edui_conf.port = EDUI_DEFAULT_PORT;
#endif
#ifdef EDUI_FORCE_IPV4
    edui_conf.mode |= EDUI_MODE_IPV4;
#endif
#ifdef EDUI_FORCE_IPV6
    edui_conf.mode |= EDUI_MODE_IPV6;
#endif
#ifdef EDUI_USE_TLS
    edui_conf.mode |= EDUI_MODE_TLS;
#endif
#ifdef EDUI_USE_PERSIST
    edui_conf.mode |= EDUI_MODE_PERSIST;
#endif
#ifdef EDUI_PERSIST_TIMEOUT
    edui_conf.persist_timeout = EDUI_PERSIST_TIMEOUT;
#endif
#ifdef EDUI_GROUP_REQUIRED
    edui_conf.mode |= EDUI_MODE_GROUP;
#endif
#ifdef EDUI_DEBUG
    edui_conf.mode |= EDUI_MODE_DEBUG;
#endif
}