void
Snmp::Pdu::aggregate(const Pdu& pdu)
{
    Must(varCount() == pdu.varCount());
    ++aggrCount;
    for (variable_list* p_aggr = variables, *p_var = pdu.variables; p_var != NULL;
            p_aggr = p_aggr->next_variable, p_var = p_var->next_variable) {
        Must(p_aggr != NULL);
        Var& aggr = static_cast<Var&>(*p_aggr);
        Var& var = static_cast<Var&>(*p_var);
        if (aggr.isNull()) {
            aggr.setName(var.getName());
            aggr.copyValue(var);
        } else {
            switch (snmpAggrType(aggr.name, aggr.name_length)) {
            case atSum:
            case atAverage:
                // The mean-average division is done later
                // when the Snmp::Pdu::fixAggregate() called
                aggr += var;
                break;
            case atMax:
                if (var > aggr)
                    aggr.copyValue(var);
                break;
            case atMin:
                if (var < aggr)
                    aggr.copyValue(var);
                break;
            default:
                break;
            }
        }
    }
}