variable_list *
snmp_prfProtoFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;
    static StatCounters *f = NULL;
    static StatCounters *l = NULL;
    double x;
    int minutes;
    debugs(49, 5, "snmp_prfProtoFn: Processing request with magic " << Var->name[LEN_SQ_PRF] << "!");
    *ErrP = SNMP_ERR_NOERROR;

    switch (Var->name[LEN_SQ_PRF + 1]) {

    case PERF_PROTOSTAT_AGGR:	/* cacheProtoAggregateStats */

        switch (Var->name[LEN_SQ_PRF + 2]) {

        case PERF_PROTOSTAT_AGGR_HTTP_REQ:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.requests,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_HTTP_HITS:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.hits,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_HTTP_ERRORS:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.errors,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_HTTP_KBYTES_IN:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.kbytes_in.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_HTTP_KBYTES_OUT:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.kbytes_out.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_ICP_S:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.icp.pkts_sent,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_ICP_R:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.icp.pkts_recv,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_ICP_SKB:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.icp.kbytes_sent.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_ICP_RKB:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.icp.kbytes_recv.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_REQ:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.server.all.requests,
                                          SMI_INTEGER);
            break;

        case PERF_PROTOSTAT_AGGR_ERRORS:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.server.all.errors,
                                          SMI_INTEGER);
            break;

        case PERF_PROTOSTAT_AGGR_KBYTES_IN:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.server.all.kbytes_in.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_KBYTES_OUT:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.server.all.kbytes_out.kb,
                                          SMI_COUNTER32);
            break;

        case PERF_PROTOSTAT_AGGR_CURSWAP:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) Store::Root().currentSize() >> 10,
                                          SMI_GAUGE32);
            break;

        case PERF_PROTOSTAT_AGGR_CLIENTS:
            Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                          (snint) statCounter.client_http.clients,
                                          SMI_GAUGE32);
            break;

        default:
            *ErrP = SNMP_ERR_NOSUCHNAME;
            break;
        }

        return Answer;

    case PERF_PROTOSTAT_MEDIAN:

        if (Var->name_length == LEN_SQ_PRF + 5)
            minutes = Var->name[LEN_SQ_PRF + 4];
        else
            break;

        if ((minutes < 1) || (minutes > 60))
            break;

        f = snmpStatGet(0);

        l = snmpStatGet(minutes);

        debugs(49, 8, "median: min= " << minutes << ", " << Var->name[LEN_SQ_PRF + 3] << " l= " << l << " , f = " << f);
        debugs(49, 8, "median: l= " << l << " , f = " << f);

        switch (Var->name[LEN_SQ_PRF + 3]) {

        case PERF_MEDIAN_TIME:
            x = minutes;
            break;

        case PERF_MEDIAN_HTTP_ALL:
            x = statHistDeltaMedian(l->client_http.allSvcTime,
                                    f->client_http.allSvcTime);
            break;

        case PERF_MEDIAN_HTTP_MISS:
            x = statHistDeltaMedian(l->client_http.missSvcTime,
                                    f->client_http.missSvcTime);
            break;

        case PERF_MEDIAN_HTTP_NM:
            x = statHistDeltaMedian(l->client_http.nearMissSvcTime,
                                    f->client_http.nearMissSvcTime);
            break;

        case PERF_MEDIAN_HTTP_HIT:
            x = statHistDeltaMedian(l->client_http.hitSvcTime,
                                    f->client_http.hitSvcTime);
            break;

        case PERF_MEDIAN_ICP_QUERY:
            x = statHistDeltaMedian(l->icp.querySvcTime, f->icp.querySvcTime);
            break;

        case PERF_MEDIAN_ICP_REPLY:
            x = statHistDeltaMedian(l->icp.replySvcTime, f->icp.replySvcTime);
            break;

        case PERF_MEDIAN_DNS:
            x = statHistDeltaMedian(l->dns.svcTime, f->dns.svcTime);
            break;

        case PERF_MEDIAN_RHR:
            x = statRequestHitRatio(minutes);
            break;

        case PERF_MEDIAN_BHR:
            x = statByteHitRatio(minutes);
            break;

        case PERF_MEDIAN_HTTP_NH:
            x = statHistDeltaMedian(l->client_http.nearHitSvcTime,
                                    f->client_http.nearHitSvcTime);
            break;

        default:
            *ErrP = SNMP_ERR_NOSUCHNAME;
            return NULL;
        }

        return snmp_var_new_integer(Var->name, Var->name_length,
                                    (snint) x,
                                    SMI_INTEGER);
    }

    *ErrP = SNMP_ERR_NOSUCHNAME;
    return NULL;
}