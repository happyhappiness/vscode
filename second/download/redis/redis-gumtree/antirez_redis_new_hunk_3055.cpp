            redisLog(REDIS_WARNING,
                "Error trying to rename the temporary AOF: %s", strerror(errno));
            close(newfd);
            if (oldfd != -1) close(oldfd);
            goto cleanup;
        }

        if (server.appendfd == -1) {
            /* AOF disabled, we don't need to set the AOF file descriptor
             * to this new file, so we can close it. */
            close(newfd);
        } else {
            /* AOF enabled, replace the old fd with the new one. */
            oldfd = server.appendfd;
            server.appendfd = newfd;
            if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(newfd);
