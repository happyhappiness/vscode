variable_list *
snmp_netIdnsFn(variable_list * Var, snint * ErrP)
{
    int i, n = 0;
    variable_list *Answer = NULL;
    MemBuf tmp;
    debugs(49, 5, "snmp_netDnsFn: Processing request: " << snmpDebugOid(Var->name, Var->name_length, tmp));
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_NET + 1]) {

    case DNS_REQ:

        for (i = 0; i < nns; i++)
            n += nameservers[i].nqueries;

        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      n,
                                      SMI_COUNTER32);

        break;

    case DNS_REP:
        for (i = 0; i < nns; i++)
            n += nameservers[i].nreplies;

        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      n,
                                      SMI_COUNTER32);

        break;

    case DNS_SERVERS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      nns,
                                      SMI_COUNTER32);

        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;

        break;
    }

    return Answer;
}