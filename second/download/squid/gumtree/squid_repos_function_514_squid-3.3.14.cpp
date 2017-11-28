struct variable_list *
snmp_var_new(oid * Name, int Len) {
    struct variable_list *New;

#if DEBUG_VARS
    printf("VARS: Creating.\n");
#endif

    New = xmalloc(sizeof(*New));
    /* XXX xmalloc never returns NULL */
    if (New == NULL) {
        snmp_set_api_error(SNMPERR_OS_ERR);
        return (NULL);
    }
    memset(New, '\0', sizeof(struct variable_list));
    /*  New->next_variable = NULL; */

    New->type = ASN_NULL;
    New->name_length = Len;

    if (New->name_length == 0) {
        New->name = NULL;
        return (New);
    }
    New->name = (oid *) xmalloc(Len * sizeof(oid));
    /* XXX xmalloc never returns NULL */
    if (New->name == NULL) {
        xfree(New);
        snmp_set_api_error(SNMPERR_OS_ERR);
        return (NULL);
    }
#if DEBUG_VARS
    printf("VARS: Copying name, size (%d)\n", Len);
#endif

    /* Only copy a name if it was specified. */
    if (Name)
        memcpy((char *) New->name, (char *) Name, Len * sizeof(oid));

    return (New);
}