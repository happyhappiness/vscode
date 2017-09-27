    }


    st = (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
                                                   &ldap_module);

    /* loop trying to bind up to st->retries times if LDAP_SERVER_DOWN or LDAP_TIMEOUT
     * are returned.  Close the connection before the first retry, and then on every
     * other retry.
     *
     * On Success or any other error, break out of the loop.
     *
     * NOTE: Looping is probably not a great idea. If the server isn't
     * responding the chances it will respond after a few tries are poor.
     * However, the original code looped and it only happens on
     * the error condition.
     */

    while (failures <= st->retries) {
        if (failures > 0 && st->retry_delay > 0) {
            apr_sleep(st->retry_delay);
        }
        rc = uldap_simple_bind(ldc, (char *)ldc->binddn, (char *)ldc->bindpw,
                               st->opTimeout);

        if (rc == LDAP_SUCCESS) break;

        failures++;

        if (AP_LDAP_IS_SERVER_DOWN(rc)) {
             ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "ldap_simple_bind() failed with server down "
                          "(try %d)", failures);
        }
        else if (rc == LDAP_TIMEOUT) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01284)
                          "ldap_simple_bind() timed out on %s "
                          "connection, dropped by firewall?",
                          new_connection ? "new" : "reused");
        }
        else {
            /* Other errors not retryable */
            break;
        }

        if (!(failures % 2)) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "attempt to re-init the connection");
            uldap_connection_unbind(ldc);
            if (LDAP_SUCCESS != uldap_connection_init(r, ldc)) {
                /* leave rc as the initial bind return code */
                break;
            }
        }
    }

    /* free the handle if there was an error
    */
    if (LDAP_SUCCESS != rc)
    {
