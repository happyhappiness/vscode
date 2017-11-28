mb->Printf("%s %s %s/%d.%d\r\n",
               RequestMethodStr(request->method),
               url && *url ? url : "/",
               AnyP::ProtocolType_str[httpver.protocol],
               httpver.major,httpver.minor);