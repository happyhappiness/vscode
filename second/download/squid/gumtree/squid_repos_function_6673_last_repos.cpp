void
Snmp::Pdu::fixAggregate()
{
    if (aggrCount < 2)
        return;
    for (variable_list* p_aggr = variables; p_aggr != NULL; p_aggr = p_aggr->next_variable) {
        Var& aggr = static_cast<Var&>(*p_aggr);
        if (snmpAggrType(aggr.name, aggr.name_length) == atAverage) {
            aggr /= aggrCount;
        }
    }
    aggrCount = 0;
}