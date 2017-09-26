                if (str[j] >= 'a' && str[j] <= 'z') {
                    str[j] = str[j] - ('a' - 'A');
                }
                j++;
            }
            apr_table_setn(e, str, vals[i]);

            /* handle remote_user_attribute, if set */
            if (sec->remote_user_attribute && 
                !strcmp(sec->remote_user_attribute, sec->attributes[i])) {
                r->user = (char *)apr_pstrdup(r->pool, vals[i]);
                remote_user_attribute_set = 1;
            }
            i++;
        }
    }

    /* sanity check */
    if (sec->remote_user_attribute && !remote_user_attribute_set) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
                  "REMOTE_USER was to be set with attribute '%s', "
                  "but this attribute was not requested for in the "
                  "LDAP query for the user. REMOTE_USER will fall "
                  "back to username or DN as appropriate.", getpid(),
                  sec->remote_user_attribute);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: accepting %s", getpid(), user);

    return AUTH_GRANTED;
}

