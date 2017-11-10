static int LDAP_rebindproc(LDAP *ld, char **binddnp, char **passwdp, int *methodp, int freeit)
{
    if (!freeit) {
        apr_ldap_rebind_entry_t *my_conn;

        *methodp = LDAP_AUTH_SIMPLE;
        my_conn = apr_ldap_rebind_lookup(ld);

        if ((my_conn) && (my_conn->bindDN != NULL)) {
            *binddnp = strdup(my_conn->bindDN);
            *passwdp = strdup(my_conn->bindPW);
        } else {
            *binddnp = NULL;
            *passwdp = NULL;
        }
    } else {
        if (*binddnp) {
            free(*binddnp);
        }
        if (*passwdp) {
            free(*passwdp);
        }
    }

    return LDAP_SUCCESS;
}