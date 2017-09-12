info = sdscatprintf(info,"slave%d:%s,%d,%s,%lld\r\n",
                    slaveid,ip,slave->slave_listening_port,state,
                    slave->repl_ack_off);