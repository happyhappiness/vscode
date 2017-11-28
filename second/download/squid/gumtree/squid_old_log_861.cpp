storeAppendPrintf(sentry, " %45.45s-%3s\n",
                              i->addrs.in_addrs[k].NtoA(buf,MAX_IPSTRLEN),
                              i->addrs.bad_mask[k] ? "BAD" : "OK ");