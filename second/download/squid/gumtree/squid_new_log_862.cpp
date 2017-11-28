storeAppendPrintf(sentry, "%s %45.45s-%3s\n",
                              "                                                         ", /* blank-space indenting IP list */
                              i->addrs.in_addrs[k].toStr(buf,MAX_IPSTRLEN),
                              i->addrs.bad_mask[k] ? "BAD" : "OK ");