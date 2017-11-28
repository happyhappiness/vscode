variable_list *
snmp_prfSysFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;

    static struct rusage rusage;
    debugs(49, 5, "snmp_prfSysFn: Processing request with magic " << Var->name[LEN_SQ_PRF + 1] << "!");
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_PRF + 1]) {

    case PERF_SYS_PF:
        squid_getrusage(&rusage);
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      rusage_pagefaults(&rusage),
                                      SMI_COUNTER32);
        break;

    case PERF_SYS_NUMR:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      IOStats.Http.reads,
                                      SMI_COUNTER32);
        break;

    case PERF_SYS_MEMUSAGE:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) statMemoryAccounted() >> 10,
                                      ASN_INTEGER);
        break;

    case PERF_SYS_CPUTIME:
        squid_getrusage(&rusage);
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) rusage_cputime(&rusage),
                                      ASN_INTEGER);
        break;

    case PERF_SYS_CPUUSAGE:
        squid_getrusage(&rusage);
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) Math::doublePercent(rusage_cputime(&rusage), tvSubDsec(squid_start, current_time)),
                                      ASN_INTEGER);
        break;

    case PERF_SYS_MAXRESSZ:
        squid_getrusage(&rusage);
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) rusage_maxrss(&rusage),
                                      ASN_INTEGER);
        break;

    case PERF_SYS_CURLRUEXP:
        /* No global LRU info anymore */
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      0,
                                      SMI_TIMETICKS);
        break;

    case PERF_SYS_CURUNLREQ:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) statCounter.unlink.requests,
                                      SMI_GAUGE32);
        break;

    case PERF_SYS_CURUNUSED_FD:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) Squid_MaxFD - Number_FD,
                                      SMI_GAUGE32);
        break;

    case PERF_SYS_CURRESERVED_FD:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) RESERVED_FD,
                                      SMI_GAUGE32);
        break;

    case PERF_SYS_CURUSED_FD:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) Number_FD,
                                      SMI_GAUGE32);
        break;

    case PERF_SYS_CURMAX_FD:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) Biggest_FD,
                                      SMI_GAUGE32);
        break;

    case PERF_SYS_NUMOBJCNT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) StoreEntry::inUseCount(),
                                      SMI_GAUGE32);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        break;
    }

    return Answer;
}