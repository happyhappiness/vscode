            if ( request->client_addr.isNoAddr() )
                strFwd = "unknown";
            else
                strFwd = request->client_addr.toStr(ntoabuf, MAX_IPSTRLEN);
        }
        if (strFwd.size() > 0)
            hdr_out->putStr(Http::HdrType::X_FORWARDED_FOR, strFwd.termedBuf());
    }
    /** If set to DELETE - do not copy through. */

    /* append Host if not there already */
    if (!hdr_out->has(Http::HdrType::HOST)) {
        if (request->peer_domain) {
            hdr_out->putStr(Http::HdrType::HOST, request->peer_domain);
        } else {
            SBuf authority = request->url.authority();
            hdr_out->putStr(Http::HdrType::HOST, authority.c_str());
        }
    }

    /* append Authorization if known in URL, not in header and going direct */
    if (!hdr_out->has(Http::HdrType::AUTHORIZATION)) {
        if (!request->flags.proxying && !request->url.userInfo().isEmpty()) {
            static uint8_t result[base64_encode_len(MAX_URL*2)]; // should be big enough for a single URI segment
            struct base64_encode_ctx ctx;
            base64_encode_init(&ctx);
            size_t blen = base64_encode_update(&ctx, result, request->url.userInfo().length(), reinterpret_cast<const uint8_t*>(request->url.userInfo().rawContent()));
            blen += base64_encode_final(&ctx, result+blen);
            result[blen] = '\0';
            if (blen)
                httpHeaderPutStrf(hdr_out, Http::HdrType::AUTHORIZATION, "Basic %.*s", (int)blen, result);
        }
    }

    /* Fixup (Proxy-)Authorization special cases. Plain relaying dealt with above */
    httpFixupAuthentication(request, hdr_in, hdr_out, flags);

