static apr_status_t uldap_connection_cleanup(void *param)
{
    util_ldap_connection_t *ldc = param;

    if (ldc) {
        /* Release the rebind info for this connection. No more referral rebinds required. */
        apr_ldap_rebind_remove(ldc->ldap);

        /* unbind and disconnect from the LDAP server */
        uldap_connection_unbind(ldc);

        /* free the username and password */
        if (ldc->bindpw) {
            free((void*)ldc->bindpw);
            ldc->bindpw = NULL;
        }
        if (ldc->binddn) {
            free((void*)ldc->binddn);
            ldc->binddn = NULL;
        }
        /* ldc->reason is allocated from r->pool */
        if (ldc->reason) {
            ldc->reason = NULL;
        }
        /* unlock this entry */
        uldap_connection_close(ldc);

    }

    return APR_SUCCESS;
}