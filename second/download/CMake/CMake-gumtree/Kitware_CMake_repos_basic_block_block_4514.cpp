{
    ldap_proto = LDAP_VERSION2;
    ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#ifdef USE_WIN32_LDAP
    rc = ldap_win_bind(conn, server, user, passwd);
#else
    rc = ldap_simple_bind_s(server, user, passwd);
#endif
  }