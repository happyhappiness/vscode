mb.Printf(SQUIDSBUFPH " " SQUIDSTRINGPH " %s/%d.%d\n",
                      SQUIDSBUFPRINT(request->method.image()),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      AnyP::ProtocolType_str[request->http_ver.protocol],
                      request->http_ver.major, request->http_ver.minor);