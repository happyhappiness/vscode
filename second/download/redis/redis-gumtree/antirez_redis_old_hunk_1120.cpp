            goto cleanup;
        } else if (server.stop_writes_on_bgsave_err &&
                   server.saveparamslen > 0 &&
                   server.lastbgsave_status == REDIS_ERR)
        {
            luaPushError(lua, shared.bgsaveerr->ptr);
            goto cleanup;
