info = sdscatprintf(info,
                    "slave%d:ip=%s,port=%d,state=%s,"
                    "offset=%lld,lag=%ld\r\n",
                    slaveid,ip,slave->slave_listening_port,state,
                    slave->repl_ack_off, lag);