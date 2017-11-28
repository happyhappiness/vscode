void
Adaptation::ServiceGroup::finalize()
{
    // 1) warn if services have different methods or vectoring point
    // 2) warn if all-same services have different bypass status
    // 3) warn if there are seemingly identical services in the group
    // TODO: optimize by remembering ServicePointers rather than IDs

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
                    debugs(93,0, "WARNING: Inconsistent bypass in " << kind <<
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