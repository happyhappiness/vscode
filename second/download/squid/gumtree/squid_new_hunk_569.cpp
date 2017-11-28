                debugs(11, DBG_IMPORTANT, "Warning: likely forwarding loop with " << url);
            }
        }

        if (strcmp(opt_forwarded_for, "on") == 0) {
            /** If set to ON - append client IP or 'unknown'. */
            if ( request->client_addr.isNoAddr() )
                strListAdd(&strFwd, "unknown", ',');
            else
                strListAdd(&strFwd, request->client_addr.toStr(ntoabuf, MAX_IPSTRLEN), ',');
        } else if (strcmp(opt_forwarded_for, "off") == 0) {
            /** If set to OFF - append 'unknown'. */
            strListAdd(&strFwd, "unknown", ',');
        } else if (strcmp(opt_forwarded_for, "transparent") == 0) {
            /** If set to TRANSPARENT - pass through unchanged. */
        } else if (strcmp(opt_forwarded_for, "truncate") == 0) {
            /** If set to TRUNCATE - drop existing list and replace with client IP or 'unknown'. */
            if ( request->client_addr.isNoAddr() )
                strFwd = "unknown";
            else
                strFwd = request->client_addr.toStr(ntoabuf, MAX_IPSTRLEN);
        }
        if (strFwd.size() > 0)
            hdr_out->putStr(HDR_X_FORWARDED_FOR, strFwd.termedBuf());
    }
    /** If set to DELETE - do not copy through. */

