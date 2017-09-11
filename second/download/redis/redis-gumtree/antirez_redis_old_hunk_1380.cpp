            log = sdscatlen(log,s,len);
        }
    }
    redisLogRaw(level,log);
    sdsfree(log);
    return 0;
}
