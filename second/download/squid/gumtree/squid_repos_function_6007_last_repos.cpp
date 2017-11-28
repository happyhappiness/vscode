int nds_get_password(
    LDAP *ld,
    char *object_dn,
    size_t *pwd_len,
    char *pwd )
{
    int rc = -1;

    rc = nmasldap_get_password(ld, object_dn, pwd_len, (unsigned char *)pwd);
    if (rc == LDAP_SUCCESS) {
#ifdef DEBUG_PASSWORD
        DEBUG(100,("nmasldap_get_password returned %s for %s\n", pwd, object_dn));
#endif
        DEBUG(5, ("NDS Universal Password retrieved for %s\n", object_dn));
    } else {
        DEBUG(3, ("NDS Universal Password NOT retrieved for %s\n", object_dn));
    }

    if (rc != LDAP_SUCCESS) {
        rc = nmasldap_get_simple_pwd(ld, object_dn, *pwd_len, pwd);
        if (rc == LDAP_SUCCESS) {
#ifdef DEBUG_PASSWORD
            DEBUG(100,("nmasldap_get_simple_pwd returned %s for %s\n", pwd, object_dn));
#endif
            DEBUG(5, ("NDS Simple Password retrieved for %s\n", object_dn));
        } else {
            /* We couldn't get the password */
            DEBUG(3, ("NDS Simple Password NOT retrieved for %s\n", object_dn));
            return LDAP_INVALID_CREDENTIALS;
        }
    }

    /* We got the password */
    return LDAP_SUCCESS;
}