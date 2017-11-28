        else {
            // Use 307 for HTTP/1.1 non-GET/HEAD requests.
            if (request->method != Http::METHOD_GET && request->method != Http::METHOD_HEAD && request->http_ver >= Http::ProtocolVersion(1,1))
                status = Http::scTemporaryRedirect;
        }

        rep->setHeaders(status, NULL, "text/html", 0, 0, -1);

        if (request) {
            MemBuf redirect_location;
            redirect_location.init();
            DenyInfoLocation(name, request, redirect_location);
            httpHeaderPutStrf(&rep->header, HDR_LOCATION, "%s", redirect_location.content() );
        }

        httpHeaderPutStrf(&rep->header, HDR_X_SQUID_ERROR, "%d %s", httpStatus, "Access Denied");
    } else {
        MemBuf *content = BuildContent();
        rep->setHeaders(httpStatus, NULL, "text/html", content->contentSize(), 0, -1);
        /*
         * include some information for downstream caches. Implicit
         * replaceable content. This isn't quite sufficient. xerrno is not
         * necessarily meaningful to another system, so we really should
         * expand it. Additionally, we should identify ourselves. Someone
         * might want to know. Someone _will_ want to know OTOH, the first
