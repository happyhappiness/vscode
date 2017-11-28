void
Snmp::Pdu::clearVars()
{
    variable_list* var = variables;
    while (var != NULL) {
        variable_list* tmp = var;
        var = var->next_variable;
        snmp_var_free(tmp);
    }
    variables = NULL;
}