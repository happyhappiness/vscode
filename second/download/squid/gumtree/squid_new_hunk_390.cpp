                        ||
                        (strncasecmp(value, "Negotiate", 9) == 0 &&
                         (value[9] == '\0' || value[9] == ' '))
                        ||
                        (strncasecmp(value, "Kerberos", 8) == 0 &&
                         (value[8] == '\0' || value[8] == ' '))) {
                    if (request->flags.connectionAuthDisabled) {
                        hdr->delAt(pos, connection_auth_blocked);
                        continue;
                    }
                    request->flags.mustKeepalive = 1;
                    if (!request->flags.accelerated && !request->flags.intercepted) {
                        httpHeaderPutStrf(hdr, HDR_PROXY_SUPPORT, "Session-Based-Authentication");
                        /*
                          We send "[Proxy-]Connection: Proxy-Support" header to mark
                          Proxy-Support as a hop-by-hop header for intermediaries that do not
                          understand the semantics of this header. The RFC should have included
