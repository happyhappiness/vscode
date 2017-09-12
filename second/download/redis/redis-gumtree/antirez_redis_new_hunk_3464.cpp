        memset(data,'x',config.datasize);
        data[config.datasize] = '\0';

        benchmark("PING (inline)","PING\r\n",6);

        len = redisFormatCommand(&cmd,"PING");
        benchmark("PING",cmd,len);
        free(cmd);

        const char *argv[11];
        argv[0] = "MSET";
        for (i = 1; i < 11; i++)
            argv[i] = data;
        len = redisFormatCommandArgv(&cmd,11,argv,NULL);
        benchmark("MSET (10 keys)",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
        benchmark("SET",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
        benchmark("GET",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
        benchmark("INCR",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
        benchmark("LPUSH",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LPOP mylist");
        benchmark("LPOP",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
        benchmark("SADD",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"SPOP myset");
        benchmark("SPOP",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
        benchmark("LPUSH (again, in order to bench LRANGE)",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
        benchmark("LRANGE (first 100 elements)",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
        benchmark("LRANGE (first 300 elements)",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
        benchmark("LRANGE (first 450 elements)",cmd,len);
        free(cmd);

        len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
        benchmark("LRANGE (first 600 elements)",cmd,len);
        free(cmd);

        printf("\n");
    } while(config.loop);
