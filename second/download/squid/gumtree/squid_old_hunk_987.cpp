
        if (s->defaultsite)
            storeAppendPrintf(e, " defaultsite=%s", s->defaultsite);

        // TODO: compare against prefix of 'n' instead of assuming http_port
        if (s->transport.protocol != AnyP::PROTO_HTTP)
            storeAppendPrintf(e, " protocol=%s", AnyP::UriScheme(s->transport.protocol).c_str());

        if (s->allow_direct)
            storeAppendPrintf(e, " allow-direct");

        if (s->ignore_cc)
            storeAppendPrintf(e, " ignore-cc");
