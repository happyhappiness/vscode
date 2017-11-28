variable_list *
snmp_sysFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    MemBuf tmp;
    debugs(49, 5, "snmp_sysFn: Processing request:" << snmpDebugOid(Var->name, Var->name_length, tmp));
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_SYS]) {

    case SYSVMSIZ:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      mem_node::StoreMemSize() >> 10,
                                      ASN_INTEGER);
        break;

    case SYSSTOR:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      store_swap_size,
                                      ASN_INTEGER);
        break;

    case SYS_UPTIME:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (int)(tvSubDsec(squid_start, current_time) * 100),
                                      SMI_TIMETICKS);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        break;
    }

    return Answer;
}