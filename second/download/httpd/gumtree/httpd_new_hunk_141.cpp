            sec->filter = apr_pstrdup(cmd->pool, urld->lud_filter);
        }
    }
    else {
        sec->filter = "objectclass=*";
    }

      /* "ldaps" indicates secure ldap connections desired
      */
    if (strncasecmp(url, "ldaps", 5) == 0)
    {
        sec->secure = 1;
        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server,
                     "LDAP: auth_ldap using SSL connections");
    }
    else
    {
        sec->secure = 0;
        sec->port = urld->lud_port? urld->lud_port : LDAP_PORT;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, 
                     "LDAP: auth_ldap not using SSL connections");
    }

    sec->have_ldap_url = 1;
    apr_ldap_free_urldesc(urld);
    return NULL;
}
