        Http::StatusCode status = Http::scFound;
        // Use configured 3xx reply status if set.
        if (name[0] == '3')
            status = httpStatus;
        else {
            // Use 307 for HTTP/1.1 non-GET/HEAD requests.
            if (request->method != Http::METHOD_GET && request->method != Http::METHOD_HEAD && request->http_ver >= Http::ProtocolVersion(1,1))
                status = Http::scTemporaryRedirect;
        }

        rep->setHeaders(status, NULL, "text/html;charset=utf-8", 0, 0, -1);

        if (request) {
            MemBuf redirect_location;
            redirect_location.init();
            DenyInfoLocation(name, request, redirect_location);
            httpHeaderPutStrf(&rep->header, HDR_LOCATION, "%s", redirect_location.content() );
        }

        httpHeaderPutStrf(&rep->header, HDR_X_SQUID_ERROR, "%d %s", httpStatus, "Access Denied");
    } else {
        MemBuf *content = BuildContent();
        rep->setHeaders(httpStatus, NULL, "text/html;charset=utf-8", content->contentSize(), 0, -1);
        /*
         * include some information for downstream caches. Implicit
         * replaceable content. This isn't quite sufficient. xerrno is not
         * necessarily meaningful to another system, so we really should
         * expand it. Additionally, we should identify ourselves. Someone
         * might want to know. Someone _will_ want to know OTOH, the first
         * X-CACHE-MISS entry should tell us who.
         */
        httpHeaderPutStrf(&rep->header, HDR_X_SQUID_ERROR, "%s %d", name, xerrno);

#if USE_ERR_LOCALES
        /*
         * If error page auto-negotiate is enabled in any way, send the Vary.
         * RFC 2616 section 13.6 and 14.44 says MAY and SHOULD do this.
         * We have even better reasons though:
         * see http://wiki.squid-cache.org/KnowledgeBase/VaryNotCaching
         */
        if (!Config.errorDirectory) {
            /* We 'negotiated' this ONLY from the Accept-Language. */
            rep->header.delById(HDR_VARY);
            rep->header.putStr(HDR_VARY, "Accept-Language");
        }

        /* add the Content-Language header according to RFC section 14.12 */
        if (err_language) {
            rep->header.putStr(HDR_CONTENT_LANGUAGE, err_language);
        } else
#endif /* USE_ERROR_LOCALES */
        {
            /* default templates are in English */
            /* language is known unless error_directory override used */
            if (!Config.errorDirectory)
                rep->header.putStr(HDR_CONTENT_LANGUAGE, "en");
        }

        rep->body.setMb(content);
        /* do not memBufClean() or delete the content, it was absorbed by httpBody */
    }

