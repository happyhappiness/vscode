{
      ldapconninfo *li = conn->proto.generic;
      ldap_abandon_ext(li->ld, lr->msgid, NULL, NULL);
      lr->msgid = 0;
    }