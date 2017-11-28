        storeAppendPrintf(e, " intercept");

    else if (s->spoof_client_ip)
        storeAppendPrintf(e, " tproxy");

    else if (s->accel) {
        if (s->vhost)
            storeAppendPrintf(e, " vhost");

        if (s->vport < 0)
            storeAppendPrintf(e, " vport");
        else if (s->vport > 0)
