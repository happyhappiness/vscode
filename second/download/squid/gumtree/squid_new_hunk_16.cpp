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

struct variable_list *
snmp_var_new_integer(oid * Name, int Len, int ival, unsigned char type) {
