static int cldap_read_host(user_data_t *ud) /* {{{ */
{
  cldap_t *st;
  LDAPMessage *result;
  char *dn;
  int rc;
  int status;

  char *attrs[9] = {
      "monitorCounter", "monitorOpCompleted", "monitorOpInitiated",
      "monitoredInfo",  "olmBDBEntryCache",   "olmBDBDNCache",
      "olmBDBIDLCache", "namingContexts",     NULL};

  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("openldap plugin: cldap_read_host: Invalid user data.");
    return (-1);
  }

  st = (cldap_t *)ud->data;

  status = cldap_init_host(st);
  if (status != 0)
    return (-1);

  rc = ldap_search_ext_s(st->ld, "cn=Monitor", LDAP_SCOPE_SUBTREE,
                         "(|(!(cn=* *))(cn=Database*))", attrs, 0, NULL, NULL,
                         NULL, 0, &result);

  if (rc != LDAP_SUCCESS) {
    ERROR("openldap plugin: Failed to execute search: %s", ldap_err2string(rc));
    ldap_msgfree(result);
    st->state = 0;
    ldap_unbind_ext_s(st->ld, NULL, NULL);
    return (-1);
  }

  for (LDAPMessage *e = ldap_first_entry(st->ld, result); e != NULL;
       e = ldap_next_entry(st->ld, e)) {
    if ((dn = ldap_get_dn(st->ld, e)) != NULL) {
      unsigned long long counter = 0;
      unsigned long long opc = 0;
      unsigned long long opi = 0;
      unsigned long long info = 0;

      struct berval counter_data;
      struct berval opc_data;
      struct berval opi_data;
      struct berval info_data;
      struct berval olmbdb_data;
      struct berval nc_data;

      struct berval **counter_list;
      struct berval **opc_list;
      struct berval **opi_list;
      struct berval **info_list;
      struct berval **olmbdb_list;
      struct berval **nc_list;

      if ((counter_list = ldap_get_values_len(st->ld, e, "monitorCounter")) !=
          NULL) {
        counter_data = *counter_list[0];
        counter = atoll(counter_data.bv_val);
      }

      if ((opc_list = ldap_get_values_len(st->ld, e, "monitorOpCompleted")) !=
          NULL) {
        opc_data = *opc_list[0];
        opc = atoll(opc_data.bv_val);
      }

      if ((opi_list = ldap_get_values_len(st->ld, e, "monitorOpInitiated")) !=
          NULL) {
        opi_data = *opi_list[0];
        opi = atoll(opi_data.bv_val);
      }

      if ((info_list = ldap_get_values_len(st->ld, e, "monitoredInfo")) !=
          NULL) {
        info_data = *info_list[0];
        info = atoll(info_data.bv_val);
      }

      if (strcmp(dn, "cn=Total,cn=Connections,cn=Monitor") == 0) {
        cldap_submit_derive("total_connections", NULL, counter, st);
      } else if (strcmp(dn, "cn=Current,cn=Connections,cn=Monitor") == 0) {
        cldap_submit_gauge("current_connections", NULL, counter, st);
      } else if (strcmp(dn, "cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "completed", opc, st);
        cldap_submit_derive("operations", "initiated", opi, st);
      } else if (strcmp(dn, "cn=Bind,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "bind-completed", opc, st);
        cldap_submit_derive("operations", "bind-initiated", opi, st);
      } else if (strcmp(dn, "cn=UnBind,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "unbind-completed", opc, st);
        cldap_submit_derive("operations", "unbind-initiated", opi, st);
      } else if (strcmp(dn, "cn=Search,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "search-completed", opc, st);
        cldap_submit_derive("operations", "search-initiated", opi, st);
      } else if (strcmp(dn, "cn=Compare,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "compare-completed", opc, st);
        cldap_submit_derive("operations", "compare-initiated", opi, st);
      } else if (strcmp(dn, "cn=Modify,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "modify-completed", opc, st);
        cldap_submit_derive("operations", "modify-initiated", opi, st);
      } else if (strcmp(dn, "cn=Modrdn,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "modrdn-completed", opc, st);
        cldap_submit_derive("operations", "modrdn-initiated", opi, st);
      } else if (strcmp(dn, "cn=Add,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "add-completed", opc, st);
        cldap_submit_derive("operations", "add-initiated", opi, st);
      } else if (strcmp(dn, "cn=Delete,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "delete-completed", opc, st);
        cldap_submit_derive("operations", "delete-initiated", opi, st);
      } else if (strcmp(dn, "cn=Abandon,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "abandon-completed", opc, st);
        cldap_submit_derive("operations", "abandon-initiated", opi, st);
      } else if (strcmp(dn, "cn=Extended,cn=Operations,cn=Monitor") == 0) {
        cldap_submit_derive("operations", "extended-completed", opc, st);
        cldap_submit_derive("operations", "extended-initiated", opi, st);
      } else if ((strncmp(dn, "cn=Database", 11) == 0) &&
                 ((nc_list = ldap_get_values_len(st->ld, e,
                                                 "namingContexts")) != NULL)) {
        nc_data = *nc_list[0];
        char typeinst[DATA_MAX_NAME_LEN];

        if ((olmbdb_list =
                 ldap_get_values_len(st->ld, e, "olmBDBEntryCache")) != NULL) {
          olmbdb_data = *olmbdb_list[0];
          ssnprintf(typeinst, sizeof(typeinst), "bdbentrycache-%s",
                    nc_data.bv_val);
          cldap_submit_gauge("cache_size", typeinst, atoll(olmbdb_data.bv_val),
                             st);
          ldap_value_free_len(olmbdb_list);
        }

        if ((olmbdb_list = ldap_get_values_len(st->ld, e, "olmBDBDNCache")) !=
            NULL) {
          olmbdb_data = *olmbdb_list[0];
          ssnprintf(typeinst, sizeof(typeinst), "bdbdncache-%s",
                    nc_data.bv_val);
          cldap_submit_gauge("cache_size", typeinst, atoll(olmbdb_data.bv_val),
                             st);
          ldap_value_free_len(olmbdb_list);
        }

        if ((olmbdb_list = ldap_get_values_len(st->ld, e, "olmBDBIDLCache")) !=
            NULL) {
          olmbdb_data = *olmbdb_list[0];
          ssnprintf(typeinst, sizeof(typeinst), "bdbidlcache-%s",
                    nc_data.bv_val);
          cldap_submit_gauge("cache_size", typeinst, atoll(olmbdb_data.bv_val),
                             st);
          ldap_value_free_len(olmbdb_list);
        }

        ldap_value_free_len(nc_list);
      } else if (strcmp(dn, "cn=Bytes,cn=Statistics,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "statistics-bytes", counter, st);
      } else if (strcmp(dn, "cn=PDU,cn=Statistics,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "statistics-pdu", counter, st);
      } else if (strcmp(dn, "cn=Entries,cn=Statistics,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "statistics-entries", counter, st);
      } else if (strcmp(dn, "cn=Referrals,cn=Statistics,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "statistics-referrals", counter, st);
      } else if (strcmp(dn, "cn=Open,cn=Threads,cn=Monitor") == 0) {
        cldap_submit_gauge("threads", "threads-open", info, st);
      } else if (strcmp(dn, "cn=Starting,cn=Threads,cn=Monitor") == 0) {
        cldap_submit_gauge("threads", "threads-starting", info, st);
      } else if (strcmp(dn, "cn=Active,cn=Threads,cn=Monitor") == 0) {
        cldap_submit_gauge("threads", "threads-active", info, st);
      } else if (strcmp(dn, "cn=Pending,cn=Threads,cn=Monitor") == 0) {
        cldap_submit_gauge("threads", "threads-pending", info, st);
      } else if (strcmp(dn, "cn=Backload,cn=Threads,cn=Monitor") == 0) {
        cldap_submit_gauge("threads", "threads-backload", info, st);
      } else if (strcmp(dn, "cn=Read,cn=Waiters,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "waiters-read", counter, st);
      } else if (strcmp(dn, "cn=Write,cn=Waiters,cn=Monitor") == 0) {
        cldap_submit_derive("derive", "waiters-write", counter, st);
      }

      ldap_value_free_len(counter_list);
      ldap_value_free_len(opc_list);
      ldap_value_free_len(opi_list);
      ldap_value_free_len(info_list);
    }

    ldap_memfree(dn);
  }

  ldap_msgfree(result);
  return (0);
}