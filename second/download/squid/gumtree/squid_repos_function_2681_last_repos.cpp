variable_list *
snmp_netFqdnFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    MemBuf tmp;
    debugs(49, 5, "snmp_netFqdnFn: Processing request:" << snmpDebugOid(Var->name, Var->name_length, tmp));
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_NET + 1]) {

    case FQDN_ENT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      fqdncacheCount(),
                                      SMI_GAUGE32);
        break;

    case FQDN_REQ:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      FqdncacheStats.requests,
                                      SMI_COUNTER32);
        break;

    case FQDN_HITS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      FqdncacheStats.hits,
                                      SMI_COUNTER32);
        break;

    case FQDN_PENDHIT:
        /* this is now worthless */
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0,
                                      SMI_GAUGE32);
        break;

    case FQDN_NEGHIT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      FqdncacheStats.negative_hits,
                                      SMI_COUNTER32);
        break;

    case FQDN_MISS:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      FqdncacheStats.misses,
                                      SMI_COUNTER32);
        break;

    case FQDN_GHBN:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0, /* deprecated */
                                      SMI_COUNTER32);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        break;
    }

    return Answer;
}