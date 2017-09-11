                }
                if (state == NULL) continue;
                info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
                    slaveid,ip,port,state);
                slaveid++;
            }
        }
