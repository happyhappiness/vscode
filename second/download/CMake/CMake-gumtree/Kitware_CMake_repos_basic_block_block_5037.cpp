{
      ldap_unbind_ext(li->ld, NULL, NULL);
      li->ld = NULL;
    }