addReplyErrorFormat(c,"REPLCONF ip-address provided by "
                    "slave instance is too long: %zd bytes", sdslen(ip));