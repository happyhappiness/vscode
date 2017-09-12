cmd = sdscatprintf(cmd,"$%lu\r\n",
            (unsigned long)sdslen(argv[j]));