void *
lutil_sasl_defaults(
    LDAP * ld,
    char *mech,
    char *realm,
    char *authcid,
    char *passwd,
    char *authzid)
{
    lutilSASLdefaults *defaults;

    defaults = (lutilSASLdefaults *) xmalloc(sizeof(lutilSASLdefaults));

    if (defaults == NULL)
        return NULL;

    defaults->mech = mech ? xstrdup(mech) : NULL;
    defaults->realm = realm ? xstrdup(realm) : NULL;
    defaults->authcid = authcid ? xstrdup(authcid) : NULL;
    defaults->passwd = passwd ? xstrdup(passwd) : NULL;
    defaults->authzid = authzid ? xstrdup(authzid) : NULL;

    if (defaults->mech == NULL) {
        ldap_get_option(ld, LDAP_OPT_X_SASL_MECH, &defaults->mech);
    }
    if (defaults->realm == NULL) {
        ldap_get_option(ld, LDAP_OPT_X_SASL_REALM, &defaults->realm);
    }
    if (defaults->authcid == NULL) {
        ldap_get_option(ld, LDAP_OPT_X_SASL_AUTHCID, &defaults->authcid);
    }
    if (defaults->authzid == NULL) {
        ldap_get_option(ld, LDAP_OPT_X_SASL_AUTHZID, &defaults->authzid);
    }
    defaults->resps = NULL;
    defaults->nresps = 0;

    return defaults;
}