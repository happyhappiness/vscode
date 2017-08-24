{
    failf(data, "LDAP local: ldap_search_ext %s", ldap_err2string(rc));
    return CURLE_LDAP_SEARCH_FAILED;
  }