    fatal("expected ICP opcode\n");

    return LOG_UDP_INVALID;
}

void
icpCreateAndSend(icp_opcode opcode, int flags, char const *url, int reqnum, int pad, int fd, const Ip::Address &from)
{
    icp_common_t *reply = _icp_common_t::createMessage(opcode, flags, url, reqnum, pad);
    icpUdpSend(fd, from, reply, icpLogFromICPCode(opcode), 0);
}

void
icpDenyAccess(Ip::Address &from, char *url, int reqnum, int fd)
{
    debugs(12, 2, "icpDenyAccess: Access Denied for " << from << " by " << AclMatchedName << ".");

    if (clientdbCutoffDenied(from)) {
        /*
         * count this DENIED query in the clientdb, even though
         * we're not sending an ICP reply...
         */
        clientdbUpdate(from, LOG_UDP_DENIED, AnyP::PROTO_ICP, 0);
    } else {
        icpCreateAndSend(ICP_DENIED, 0, url, reqnum, 0, fd, from);
    }
}

bool
icpAccessAllowed(Ip::Address &from, HttpRequest * icp_request)
{
    /* absent an explicit allow, we deny all */
    if (!Config.accessList.icp)
        return true;

    ACLFilledChecklist checklist(Config.accessList.icp, icp_request, NULL);
    checklist.src_addr = from;
    checklist.my_addr.SetNoAddr();
    return (checklist.fastCheck() == ACCESS_ALLOWED);
}

char const *
icpGetUrlToSend(char *url)
{
    if (strpbrk(url, w_space))
        return rfc1738_escape(url);
    else
        return url;
}

HttpRequest *
icpGetRequest(char *url, int reqnum, int fd, Ip::Address &from)
{
    if (strpbrk(url, w_space)) {
        url = rfc1738_escape(url);
        icpCreateAndSend(ICP_ERR, 0, rfc1738_escape(url), reqnum, 0, fd, from);
        return NULL;
    }
