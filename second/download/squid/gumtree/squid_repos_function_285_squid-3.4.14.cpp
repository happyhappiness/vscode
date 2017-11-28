int
lutil_sasl_interact(
    LDAP * ld,
    unsigned flags,
    void *defaults,
    void *in)
{
    sasl_interact_t *interact = (sasl_interact_t *) in;

    if (ld == NULL)
        return LDAP_PARAM_ERROR;

    while (interact->id != SASL_CB_LIST_END) {
        int rc = interaction(flags, interact, (lutilSASLdefaults *) defaults);

        if (rc)
            return rc;
        ++interact;
    }

    return LDAP_SUCCESS;
}