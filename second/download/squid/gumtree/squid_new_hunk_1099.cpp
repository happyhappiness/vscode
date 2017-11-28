        request->flags.cachable = false;
        /* pretend it's not a range request */
        request->ignoreRange("want to request the whole object");
        request->flags.isRanged = false;
    }

    hdr_out->addVia(request->http_ver, hdr_in);

    if (request->flags.accelerated) {
        /* Append Surrogate-Capabilities */
        String strSurrogate(hdr_in->getList(Http::HdrType::SURROGATE_CAPABILITY));
#if USE_SQUID_ESI
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0 ESI/1.0\"", Config.Accel.surrogate_id);
#else
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0\"", Config.Accel.surrogate_id);
#endif
        strListAdd(&strSurrogate, bbuf, ',');
        hdr_out->putStr(Http::HdrType::SURROGATE_CAPABILITY, strSurrogate.termedBuf());
    }

    /** \pre Handle X-Forwarded-For */
    if (strcmp(opt_forwarded_for, "delete") != 0) {

        String strFwd = hdr_in->getList(Http::HdrType::X_FORWARDED_FOR);

        // if we cannot double strFwd size, then it grew past 50% of the limit
        if (!strFwd.canGrowBy(strFwd.size())) {
            // There is probably a forwarding loop with Via detection disabled.
            // If we do nothing, String will assert on overflow soon.
            // TODO: Terminate all transactions with huge XFF?
            strFwd = "error";

            static int warnedCount = 0;
            if (warnedCount++ < 100) {
                const SBuf url(entry ? SBuf(entry->url()) : request->effectiveRequestUri());
                debugs(11, DBG_IMPORTANT, "Warning: likely forwarding loop with " << url);
            }
        }

        if (strcmp(opt_forwarded_for, "on") == 0) {
            /** If set to ON - append client IP or 'unknown'. */
