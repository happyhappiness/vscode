static apr_status_t uldap_connection_cleanup(void *param)
{
    util_ldap_connection_t *ldc = param;

    if (ldc) {

        /* unbind and disconnect from the LDAP server */
        uldap_connection_unbind(ldc);

        /* free the username and password */
        if (ldc->bindpw) {
            free((void*)ldc->bindpw);
        }
        if (ldc->binddn) {
            free((void*)ldc->binddn);
        }

        /* unlock this entry */
        uldap_connection_close(ldc);

    }

    return APR_SUCCESS;
}