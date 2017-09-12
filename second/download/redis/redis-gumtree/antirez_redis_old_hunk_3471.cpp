        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
        {
            int i;
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
            for (i = 0; i < 10; i++) {
                c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
            }
