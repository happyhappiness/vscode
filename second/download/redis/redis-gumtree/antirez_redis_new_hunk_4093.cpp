            len++;
        }
    }
    buf[0] = '$';
    intlen = ll2string(buf+1,sizeof(buf)-1,(long long)len);
    buf[intlen+1] = '\r';
    buf[intlen+2] = '\n';
    addReplySds(c,sdsnewlen(buf,intlen+3));
}

static void addReplyBulk(redisClient *c, robj *obj) {
