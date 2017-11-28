int
Snmp::Pdu::varCount() const
{
    int count = 0;
    for (variable_list* var = variables; var != NULL; var = var->next_variable)
        ++count;
    return count;
}