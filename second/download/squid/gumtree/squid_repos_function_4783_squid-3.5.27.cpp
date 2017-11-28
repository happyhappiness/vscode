int
ACLDestinationIP::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);

    // if there is no HTTP request details fallback to the dst_addr
    if (!checklist->request)
        return ACLIP::match(checklist->dst_addr);

    // Bug 3243: CVE 2009-0801
    // Bypass of browser same-origin access control in intercepted communication
    // To resolve this we will force DIRECT and only to the original client destination.
    // In which case, we also need this ACL to accurately match the destination
    if (Config.onoff.client_dst_passthru && (checklist->request->flags.intercepted || checklist->request->flags.interceptTproxy)) {
        const ConnStateData *conn = checklist->conn();
        return (conn != NULL && conn->clientConnection != NULL) ?
               ACLIP::match(conn->clientConnection->local) : -1;
    }

    if (flags.isSet(ACL_F_NO_LOOKUP)) {
        if (!checklist->request->GetHostIsNumeric()) {
            debugs(28, 3, "aclMatchAcl:  No-lookup DNS ACL '" << AclMatchedName << "' for '" << checklist->request->GetHost() << "'");
            return 0;
        }

        if (ACLIP::match(checklist->request->host_addr))
            return 1;
        return 0;
    }

    const ipcache_addrs *ia = ipcache_gethostbyname(checklist->request->GetHost(), IP_LOOKUP_IF_MISS);

    if (ia) {
        /* Entry in cache found */

        for (int k = 0; k < (int) ia->count; ++k) {
            if (ACLIP::match(ia->in_addrs[k]))
                return 1;
        }

        return 0;
    } else if (!checklist->request->flags.destinationIpLookedUp) {
        /* No entry in cache, lookup not attempted */
        debugs(28, 3, "aclMatchAcl: Can't yet compare '" << name << "' ACL for '" << checklist->request->GetHost() << "'");
        if (checklist->goAsync(DestinationIPLookup::Instance()))
            return -1;
        // else fall through to mismatch, hiding the lookup failure (XXX)
    }

    return 0;
}