line = sdscatprintf(sdsempty(),"sentinel announce-port %d",
                            sentinel.announce_port);