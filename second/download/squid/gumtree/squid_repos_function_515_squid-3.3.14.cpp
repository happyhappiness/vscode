struct variable_list *
snmp_var_new_integer(oid * Name, int Len, int ival, unsigned char type) {
    variable_list *v = snmp_var_new(Name, Len);
    v->val_len = sizeof(int);
    v->val.integer = xmalloc(sizeof(int));
    v->type = type;
    *(v->val.integer) = ival;
    return v;
}