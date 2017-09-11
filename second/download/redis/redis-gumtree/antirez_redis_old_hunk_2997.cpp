        benchmark("LRANGE (first 600 elements)",cmd,len);
        free(cmd);

        printf("\n");
    } while(config.loop);

    return 0;
