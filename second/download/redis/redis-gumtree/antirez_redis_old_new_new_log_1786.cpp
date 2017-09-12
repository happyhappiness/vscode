sdscatprintf(sdsempty(),
                "-MISCONF Errors writing to the AOF file: %s\r\n",
                strerror(server.aof_last_write_errno));