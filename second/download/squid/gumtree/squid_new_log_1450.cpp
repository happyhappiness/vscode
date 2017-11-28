mb->appendf(SQUIDSBUFPH " " SQUIDSBUFPH " %s/%d.%d\r\n",
                SQUIDSBUFPRINT(request->method.image()),
                SQUIDSBUFPRINT(url),
                AnyP::ProtocolType_str[httpver.protocol],
                httpver.major,httpver.minor);