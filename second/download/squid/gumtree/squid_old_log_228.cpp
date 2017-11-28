mb->Printf("%s %s HTTP/%d.%d\r\n",
               RequestMethodStr(aRequest->method),
               aRequest->urlpath.size() ? aRequest->urlpath.termedBuf() : "/",
               httpver.major,httpver.minor);