storeAppendPrintf(s, "\tin: buf %p, used %ld, free %ld\n",
                              conn->in.buf.c_str(), (long int) conn->in.buf.length(), (long int) conn->in.buf.spaceSize());