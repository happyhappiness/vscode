            return sdscatprintf(sdsempty(),"-Reading from master: %s",
                    strerror(errno));
        }
        return sdsnew(buf);
    }
    return NULL;
