            storeAppendPrintf(e, " tcpkeepalive=%d,%d,%d", s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
        } else {
            storeAppendPrintf(e, " tcpkeepalive");
        }
    }

#if USE_SSL
    if (s->flags.tunnelSslBumping)
        storeAppendPrintf(e, " ssl-bump");

    if (s->cert)
        storeAppendPrintf(e, " cert=%s", s->cert);

