{
    failf(data, "LDAP local: bind ldap_parse_result %s", ldap_err2string(rc));
    return CURLE_LDAP_CANNOT_BIND;
  }