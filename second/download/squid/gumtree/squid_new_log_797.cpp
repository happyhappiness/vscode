storeAppendPrintf(sentry, "%s/%d\t",
                      addr.toStr(buf, MAX_IPSTRLEN),
                      mask.cidr() );