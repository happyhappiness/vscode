variable_list *
snmp_netDnsFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    MemBuf tmp;
    debugs(49, 5, "snmp_netDnsFn: Processing request: " << Var->name[LEN_SQ_NET + 1] << " " << snmpDebugOid(Var->name, Var->name_length, tmp));
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_NET + 1]) {

    case DNS_REQ:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      dnsservers->stats.requests,
                                      SMI_COUNTER32);
        break;

    case DNS_REP:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      dnsservers->stats.replies,
                                      SMI_COUNTER32);
        break;

    case DNS_SERVERS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      dnsservers->childs.n_running,
                                      SMI_COUNTER32);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        break;
    }

    return Answer;
}