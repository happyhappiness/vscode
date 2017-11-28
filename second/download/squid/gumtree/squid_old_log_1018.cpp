mb.Printf("%s " SQUIDSTRINGPH " %s/%d.%d\n",
                      RequestMethodStr(request->method),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      AnyP::ProtocolType_str[request->http_ver.protocol],
                      request->http_ver.major, request->http_ver.minor);