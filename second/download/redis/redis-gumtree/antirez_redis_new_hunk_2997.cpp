        benchmark("LRANGE (first 600 elements)",cmd,len);
        free(cmd);

        if (!config.csv) printf("\n");
    } while(config.loop);

    return 0;
