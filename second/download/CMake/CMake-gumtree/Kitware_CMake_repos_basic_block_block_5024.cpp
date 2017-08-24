{
      if(info) {
        ldap_memfree(info);
        info = NULL;
      }
      proto = LDAP_VERSION2;
      ldap_set_option(li->ld, LDAP_OPT_PROTOCOL_VERSION, &proto);
      li->didbind = FALSE;
      goto retry;
    }