            log = sdscatlen(log,s,len);
        }
    }
    serverLogRaw(level,log);
    sdsfree(log);
    return 0;
}
