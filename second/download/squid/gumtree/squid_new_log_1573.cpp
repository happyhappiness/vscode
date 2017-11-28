storeAppendPrintf(s, "\tin: buf %p, used %ld, free %ld\n",
                              conn->inBuf.rawContent(), (long int) conn->inBuf.length(), (long int) conn->inBuf.spaceSize());