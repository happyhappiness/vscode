storeAppendPrintf(sentry, "%s/%d\t",
                      addr.NtoA(buf, MAX_IPSTRLEN),
                      mask.GetCIDR() );