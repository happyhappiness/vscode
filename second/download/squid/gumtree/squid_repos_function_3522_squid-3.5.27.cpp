variable_list *
snmp_meshPtblFn(variable_list * Var, snint * ErrP)
{
    variable_list *Answer = NULL;

    Ip::Address laddr;
    char *cp = NULL;
    CachePeer *p = NULL;
    int cnt = 0;
    debugs(49, 5, "snmp_meshPtblFn: peer " << Var->name[LEN_SQ_MESH + 3] << " requested!");
    *ErrP = SNMP_ERR_NOERROR;

    u_int index = Var->name[LEN_SQ_MESH + 3] ;
    for (p = Config.peers; p != NULL; p = p->next, ++cnt) {
        if (p->index == index) {
            laddr = p->in_addr ;
            break;
        }
    }

    if (p == NULL) {
        *ErrP = SNMP_ERR_NOSUCHNAME;
        return NULL;
    }

    switch (Var->name[LEN_SQ_MESH + 2]) {
    case MESH_PTBL_INDEX: { // FIXME INET6: Should be visible?
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint)p->index, SMI_INTEGER);
    }
    break;

    case MESH_PTBL_NAME:
        cp = p->host;
        Answer = snmp_var_new(Var->name, Var->name_length);
        Answer->type = ASN_OCTET_STR;
        Answer->val_len = strlen(cp);
        Answer->val.string = (u_char *) xstrdup(cp);

        break;

    case MESH_PTBL_ADDR_TYPE: {
        int ival;
        ival = laddr.isIPv4() ? INETADDRESSTYPE_IPV4 : INETADDRESSTYPE_IPV6 ;
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      ival, SMI_INTEGER);
    }
    break;
    case MESH_PTBL_ADDR: {
        Answer = snmp_var_new(Var->name, Var->name_length);
        // InetAddress doesn't have its own ASN.1 type,
        // like IpAddr does (SMI_IPADDRESS)
        // See: rfc4001.txt
        Answer->type = ASN_OCTET_STR;
        char host[MAX_IPSTRLEN];
        laddr.toStr(host,MAX_IPSTRLEN);
        Answer->val_len = strlen(host);
        Answer->val.string =  (u_char *) xstrdup(host);
    }
    break;

    case MESH_PTBL_HTTP:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) p->http_port,
                                      ASN_INTEGER);
        break;

    case MESH_PTBL_ICP:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) p->icp.port,
                                      ASN_INTEGER);
        break;

    case MESH_PTBL_TYPE:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) p->type,
                                      ASN_INTEGER);
        break;

    case MESH_PTBL_STATE:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      (snint) neighborUp(p),
                                      ASN_INTEGER);
        break;

    case MESH_PTBL_SENT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.pings_sent,
                                      SMI_COUNTER32);
        break;

    case MESH_PTBL_PACKED:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.pings_acked,
                                      SMI_COUNTER32);
        break;

    case MESH_PTBL_FETCHES:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.fetches,
                                      SMI_COUNTER32);
        break;

    case MESH_PTBL_RTT:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.rtt,
                                      ASN_INTEGER);
        break;

    case MESH_PTBL_IGN:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.ignored_replies,
                                      SMI_COUNTER32);
        break;

    case MESH_PTBL_KEEPAL_S:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.n_keepalives_sent,
                                      SMI_COUNTER32);
        break;

    case MESH_PTBL_KEEPAL_R:
        Answer = snmp_var_new_integer(Var->name, Var->name_length,
                                      p->stats.n_keepalives_recv,
                                      SMI_COUNTER32);
        break;

    default:
        *ErrP = SNMP_ERR_NOSUCHNAME;
        break;
    }

    return Answer;
}