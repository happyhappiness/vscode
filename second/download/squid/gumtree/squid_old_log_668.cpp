storeAppendPrintf(s, "\tme: %s:%d\n",
                              conn->me.NtoA(buf,MAX_IPSTRLEN),
                              conn->me.GetPort());