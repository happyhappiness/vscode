f(!ludp->lud_attrs) {
      free(attributes);

      rc = LDAP_NO_MEMORY;

      goto quit;
    }