buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
                          server.replid,offset);