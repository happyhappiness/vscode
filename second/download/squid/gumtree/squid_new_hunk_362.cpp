
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
