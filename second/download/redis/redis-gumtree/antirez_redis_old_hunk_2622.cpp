        start_addr = strtoul(start,NULL,16);
        end_addr = strtoul(end,NULL,16);
        size = end_addr-start_addr;
        redisLog(REDIS_WARNING,
            "Testing memory at %lx (%lu bytes)", start_addr, size);
        for (j = 0; j < 3; j++) {
            if (memtest_non_destructive((void*)start_addr,size) != 0) {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}
#endif

