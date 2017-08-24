{
        failf(data, "LDAP local: search ldap_parse_result %s",
              ldap_err2string(rc));
        *err = CURLE_LDAP_SEARCH_FAILED;
      }