void
Adaptation::ServiceGroup::finalize()
{
    // 1) warn if services have different methods or vectoring point
    // 2) warn if all-same services have different bypass status
    // 3) warn if there are seemingly identical services in the group
    // TODO: optimize by remembering ServicePointers rather than IDs
    if (!removedServices.empty()) {
        String s;
        for (Store::iterator it = removedServices.begin(); it != removedServices.end(); ++it) {
            s.append(*it);
            s.append(',');
        }
        s.cut(s.size() - 1);
        debugs(93, DBG_IMPORTANT, "Adaptation group '" << id << "' contains disabled member(s) after reconfiguration: " << s);
        removedServices.clean();
    }

    String baselineKey;
    bool baselineBypass = false;
    for (Pos pos = 0; has(pos); ++pos) {
        // TODO: quit on all errors
        const String &serviceId = services[pos];
        ServicePointer service = at(pos);
        if (service != NULL) {
            if (method == methodNone) {
                // optimization: cache values that should be the same
                method = service->cfg().method;
                point = service->cfg().point;
            } else {
                if (method != service->cfg().method)
                    finalizeMsg("Inconsistent service method for", serviceId, true);
                if (point != service->cfg().point)
                    finalizeMsg("Inconsistent vectoring point for", serviceId, true);
            }

            checkUniqueness(pos);

            if (allServicesSame) {
                if (!baselineKey.size()) {
                    baselineKey = service->cfg().key;
                    baselineBypass = service->cfg().bypass;
                } else if (baselineBypass != service->cfg().bypass) {
                    debugs(93, DBG_CRITICAL, "WARNING: Inconsistent bypass in " << kind <<
                           ' ' << id << " may produce surprising results: " <<
                           baselineKey << " vs. " << serviceId);
                }
            }
        } else {
            finalizeMsg("ERROR: Unknown adaptation name", serviceId, true);
        }
    }
    debugs(93,7, HERE << "finalized " << kind << ": " << id);
}