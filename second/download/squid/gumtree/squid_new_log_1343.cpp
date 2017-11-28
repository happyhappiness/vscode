str.appendf(SQUIDSBUFPH " " SQUIDSBUFPH " %s/%d.%d\n",
                    SQUIDSBUFPRINT(request->method.image()),
                    SQUIDSBUFPRINT(request->url.path()),
                    AnyP::ProtocolType_str[request->http_ver.protocol],
                    request->http_ver.major, request->http_ver.minor);