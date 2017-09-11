            redisLog(REDIS_WARNING,
                "Error trying to rename the temporary AOF: %s", strerror(errno));
            close(newfd);
            if (oldfd != -1)
                close(oldfd);
            goto cleanup;
        }

        if (server.appendfd == -1) {
            /* AOF disabled */
            close(newfd);
        } else {
            /* AOF enabled */
            oldfd = server.appendfd;
            server.appendfd = newfd;
            if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(newfd);
