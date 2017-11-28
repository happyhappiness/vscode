        else if (s->vport > 0)
            storeAppendPrintf(e, " vport=%d", s->vport);

        if (s->defaultsite)
            storeAppendPrintf(e, " defaultsite=%s", s->defaultsite);

        if (s->protocol && strcmp(s->protocol,"http") != 0)
            storeAppendPrintf(e, " protocol=%s", s->protocol);

        if (s->allow_direct)
            storeAppendPrintf(e, " allow-direct");

        if (s->ignore_cc)
            storeAppendPrintf(e, " ignore-cc");
