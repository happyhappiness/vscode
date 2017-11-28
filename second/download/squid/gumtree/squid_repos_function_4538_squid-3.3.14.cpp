int
ACLDestinationIP::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);

    // Bug 3243: CVE 2009-0801
    // Bypass of browser same-origin access control in intercepted communication
    // To resolve this we will force DIRECT and only to the original client destination.
    // In which case, we also need this ACL to accurately match the destination
    if (Config.onoff.client_dst_passthru && (checklist->request->flags.intercepted || checklist->request->flags.spoofClientIp)) {
        assert(checklist->conn() && checklist->conn()->clientConnection != NULL);
        return ACLIP::match(checklist->conn()->clientConnection->local);
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
        checklist->changeState (DestinationIPLookup::Instance());
        return 0;
    } else {
        return 0;
    }
}