mb.Printf("%s " SQUIDSTRINGPH " HTTP/%d.%d\n",
                      RequestMethodStr(request->method),
                      SQUIDSTRINGPRINT(urlpath_or_slash),
                      request->http_ver.major, request->http_ver.minor);