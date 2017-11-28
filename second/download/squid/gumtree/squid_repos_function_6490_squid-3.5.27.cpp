void
Snmp::Pdu::setVars(variable_list* vars)
{
    clearVars();
    for (variable_list** p_var = &variables; vars != NULL;
            vars = vars->next_variable, p_var = &(*p_var)->next_variable) {
        *p_var = new Var(static_cast<Var&>(*vars));
    }
}