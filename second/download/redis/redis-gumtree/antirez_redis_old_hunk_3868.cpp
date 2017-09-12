            bulklen < 0 || bulklen > 1024*1024*1024)
        {
            c->argc--;
            addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
            resetClient(c);
            return 1;
        }
