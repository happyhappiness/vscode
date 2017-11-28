void
snmp_var_free(struct variable_list *Ptr)
{
    if (Ptr->name)
        xfree((char *) Ptr->name);

    if (Ptr->val.string)
        xfree((char *) Ptr->val.string);
    else if (Ptr->val.integer)
        xfree((char *) Ptr->val.integer);

    xfree(Ptr);
}