static int
interaction(
    unsigned,
    sasl_interact_t * interact,
    lutilSASLdefaults * defaults)
{
    const char *dflt = interact->defresult;

    switch (interact->id) {
    case SASL_CB_GETREALM:
        if (defaults)
            dflt = defaults->realm;
        break;
    case SASL_CB_AUTHNAME:
        if (defaults)
            dflt = defaults->authcid;
        break;
    case SASL_CB_PASS:
        if (defaults)
            dflt = defaults->passwd;
        break;
    case SASL_CB_USER:
        if (defaults)
            dflt = defaults->authzid;
        break;
    case SASL_CB_NOECHOPROMPT:
        break;
    case SASL_CB_ECHOPROMPT:
        break;
    }

    if (dflt && !*dflt)
        dflt = NULL;

    /* input must be empty */
    interact->result = (dflt && *dflt) ? dflt : "";
    interact->len = (unsigned) strlen((const char *) interact->result);

    return LDAP_SUCCESS;
}