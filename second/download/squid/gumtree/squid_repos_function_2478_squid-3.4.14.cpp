variable_list *
snmp_netIpFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    MemBuf tmp;
    debugs(49, 5, "snmp_netIpFn: Processing request:" << snmpDebugOid(Var->name, Var->name_length, tmp));
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_NET + 1]) {

    case IP_ENT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      ipcacheCount(),
                                      SMI_GAUGE32);
        break;

    case IP_REQ:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      IpcacheStats.requests,
                                      SMI_COUNTER32);
        break;

    case IP_HITS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      IpcacheStats.hits,
                                      SMI_COUNTER32);
        break;

    case IP_PENDHIT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0,
                                      SMI_GAUGE32);
        break;

    case IP_NEGHIT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      IpcacheStats.negative_hits,
                                      SMI_COUNTER32);
        break;

    case IP_MISS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      IpcacheStats.misses,
                                      SMI_COUNTER32);
        break;

    case IP_GHBN:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0, /* deprecated */
                                      SMI_COUNTER32);
        break;

    case IP_LOC:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0, /* deprecated */
                                      SMI_COUNTER32);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        snmp_var_free(Answer);
        return (NULL);
    }

    return Answer;
}