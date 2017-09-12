info = sdscatprintf(info,"cmdstat_%s:calls=%lld,usec=%lld\r\n",
                c->name, c->calls, c->microseconds);