int
ACLEui64::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);

    /* IPv4 does not do EUI-64 (yet) */
    if (!checklist->src_addr.isIPv6()) {
        debugs(14, 3, "ACLEui64::match: IPv6 Required for EUI-64 Lookups. Skipping " << checklist->src_addr );
        return 0;
    }

    Eui::Eui64 lookingFor;
    if (lookingFor.lookup(checklist->src_addr)) {
        bool found = (eui64Data.find(lookingFor) != eui64Data.end());
        debugs(28, 3,  checklist->src_addr << "' " << (found ? "found" : "NOT found"));
        return found;
    }

    debugs(28, 3, checklist->src_addr << " NOT found");
    return 0;
}