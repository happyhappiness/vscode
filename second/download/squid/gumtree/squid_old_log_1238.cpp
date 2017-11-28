storeAppendPrintf(entry, "cache_peer_domain %s %s%s\n",
                              p->host,
                              d->do_ping ? null_string : "!",
                              d->domain);