    /* NOTREACHED */
}

/**
 * Decide where details need to be gathered to correctly describe a persistent connection.
 * What is needed:
 *  -  the address/port details about this link
 *  -  domain name of server at other end of this link (either peer or requested host)
 */
void
FwdState::pconnPush(Comm::ConnectionPointer &conn, const char *domain)
{
    if (conn->getPeer()) {
        fwdPconnPool->push(conn, NULL);
    } else {
        fwdPconnPool->push(conn, domain);
    }
}

void
FwdState::initModule()
{
    RegisterWithCacheManager();
}

void
FwdState::RegisterWithCacheManager(void)
{
    Mgr::RegisterAction("forward", "Request Forwarding Statistics", fwdStats, 0, 1);
}

void
FwdState::logReplyStatus(int tries, http_status status)
{
    if (status > HTTP_INVALID_HEADER)
        return;

    assert(tries >= 0);

    if (tries > MAX_FWD_STATS_IDX)
        tries = MAX_FWD_STATS_IDX;

    ++ FwdReplyCodes[tries][status];
}

/**** PRIVATE NON-MEMBER FUNCTIONS ********************************************/

/*
 * DPW 2007-05-19
 * Formerly static, but now used by client_side_request.cc
 */
/// Checks for a TOS value to apply depending on the ACL
tos_t
aclMapTOS(acl_tos * head, ACLChecklist * ch)
{
    acl_tos *l;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
            return l->tos;
    }

    return 0;
}

/// Checks for a netfilter mark value to apply depending on the ACL
nfmark_t
aclMapNfmark(acl_nfmark * head, ACLChecklist * ch)
{
    acl_nfmark *l;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
            return l->nfmark;
    }

    return 0;
}

void
getOutgoingAddress(HttpRequest * request, Comm::ConnectionPointer conn)
{
    // skip if an outgoing address is already set.
    if (!conn->local.IsAnyAddr()) return;

    // ensure that at minimum the wildcard local matches remote protocol
    if (conn->remote.IsIPv4())
        conn->local.SetIPv4();

    // maybe use TPROXY client address
    if (request && request->flags.spoof_client_ip) {
        if (!conn->getPeer() || !conn->getPeer()->options.no_tproxy) {
#if FOLLOW_X_FORWARDED_FOR && LINUX_NETFILTER
            if (Config.onoff.tproxy_uses_indirect_client)
                conn->local = request->indirect_client_addr;
            else
#endif
                conn->local = request->client_addr;
            // some flags need setting on the socket to use this address
            conn->flags |= COMM_DOBIND;
            conn->flags |= COMM_TRANSPARENT;
            return;
        }
        // else no tproxy today ...
    }

    if (!Config.accessList.outgoing_address) {
        return; // anything will do.
    }

    ACLFilledChecklist ch(NULL, request, NULL);
    ch.dst_peer = conn->getPeer();
    ch.dst_addr = conn->remote;

    // TODO use the connection details in ACL.
    // needs a bit of rework in ACLFilledChecklist to use Comm::Connection instead of ConnStateData

    acl_address *l;
    for (l = Config.accessList.outgoing_address; l; l = l->next) {

        /* check if the outgoing address is usable to the destination */
        if (conn->remote.IsIPv4() != l->addr.IsIPv4()) continue;

        /* check ACLs for this outgoing address */
        if (!l->aclList || ch.fastCheck(l->aclList) == ACCESS_ALLOWED) {
            conn->local = l->addr;
            return;
        }
    }
}

tos_t
GetTosToServer(HttpRequest * request)
{
    ACLFilledChecklist ch(NULL, request, NULL);
    return aclMapTOS(Ip::Qos::TheConfig.tosToServer, &ch);
}

nfmark_t
GetNfmarkToServer(HttpRequest * request)
{
    ACLFilledChecklist ch(NULL, request, NULL);
    return aclMapNfmark(Ip::Qos::TheConfig.nfmarkToServer, &ch);
}
