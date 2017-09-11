                    break;
                }
                if (state == NULL) continue;
                info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
                    slaveid,ip,slave->slave_listening_port,state);
                slaveid++;
            }
        }
