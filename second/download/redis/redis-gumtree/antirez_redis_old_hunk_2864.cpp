                mem_used -= obuf_bytes;
        }
    }
    if (debug) printf("used_nosl: %zu\n", mem_used);
    if (server.aof_state != REDIS_AOF_OFF) {
        mem_used -= sdslen(server.aof_buf);
        mem_used -= sdslen(server.aof_rewrite_buf);
