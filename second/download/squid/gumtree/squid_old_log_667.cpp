storeAppendPrintf(s, "\tpeer: %s:%d\n",
                              conn->peer.NtoA(buf,MAX_IPSTRLEN),
                              conn->peer.GetPort());