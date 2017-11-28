void
snmp_add_null_var(struct snmp_pdu *pdu, oid * name, int name_length)
{
    struct variable_list *vars;
    struct variable_list *ptr;

    vars = snmp_var_new(name, name_length);
    if (vars == NULL) {
        perror("snmp_add_null_var:xmalloc");
        return;
    }
    if (pdu->variables == NULL) {
        pdu->variables = vars;
    } else {

        /* Insert at the end */
        for (ptr = pdu->variables;
                ptr->next_variable;
                ptr = ptr->next_variable)
            /*EXIT */ ;
        ptr->next_variable = vars;
    }

    return;
}