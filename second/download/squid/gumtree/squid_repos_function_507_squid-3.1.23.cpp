struct variable_list *
snmp_var_clone(struct variable_list *Src) {
    struct variable_list *Dest;

#ifdef DEBUG_VARS
    printf("VARS: Cloning.\n");
#endif

    Dest = (struct variable_list *) xmalloc(sizeof(struct variable_list));
    if (Dest == NULL) {
        snmp_set_api_error(SNMPERR_OS_ERR);
        return (NULL);
    }
#ifdef DEBUG_VARS
    printf("VARS: Copying entire variable list.  (Size %d)\n",
           sizeof(struct variable_list));
#endif

    xmemcpy((char *) Dest, (char *) Src, sizeof(struct variable_list));

    if (Src->name != NULL) {
        Dest->name = (oid *) xmalloc(Src->name_length * sizeof(oid));
        if (Dest->name == NULL) {
            snmp_set_api_error(SNMPERR_OS_ERR);
            xfree(Dest);
            return (NULL);
        }
#ifdef DEBUG_VARS
        printf("VARS: Copying name OID. (Size %d)\n", Src->name_length);
#endif
        xmemcpy((char *) Dest->name, (char *) Src->name,
                Src->name_length * sizeof(oid));
    }
    /* CISCO Catalyst 2900 returns NULL strings as data of length 0. */
    if ((Src->val.string != NULL) &&
            (Src->val_len)) {
        Dest->val.string = (u_char *) xmalloc(Src->val_len);
        if (Dest->val.string == NULL) {
            snmp_set_api_error(SNMPERR_OS_ERR);
            xfree(Dest->name);
            xfree(Dest);
            return (NULL);
        }
#ifdef DEBUG_VARS
        printf("VARS: Copying value (Size %d)\n", Src->val_len);
#endif
        xmemcpy((char *) Dest->val.string, (char *) Src->val.string, Src->val_len);
    }
#ifdef DEBUG_VARS
    printf("VARS: Cloned %x.\n", (unsigned int) Dest);
#endif
#ifdef DEBUG_VARS_MALLOC
    printf("VARS: Cloned  (%x)\n", (unsigned int) Dest);
    printf("VARS: Name is (%x)\n", (unsigned int) Dest->name);
#endif

    return (Dest);
}