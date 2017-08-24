f(err) {
    failf(data, "LDAP remote: bind failed %s %s", ldap_err2string(rc),
          info ? info : "");
    if(info)
      ldap_memfree(info);
    return CURLE_LOGIN_DENIED;
  }