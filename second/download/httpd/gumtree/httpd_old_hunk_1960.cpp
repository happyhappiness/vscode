                if (str[j] >= 'a' && str[j] <= 'z') {
                    str[j] = str[j] - ('a' - 'A');
                }
                j++;
            }
            apr_table_setn(e, str, vals[i]);
            i++;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: accepting %s", getpid(), user);

    return AUTH_GRANTED;
}

