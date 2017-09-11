            return REDIS_ERR;
        }
    } else if (nread == 0) {
        __redisSetError(c,REDIS_ERR_EOF,
            sdsnew("Server closed the connection"));
        return REDIS_ERR;
    } else {
        __redisCreateReplyReader(c);
        redisReplyReaderFeed(c->reader,buf,nread);
    }
    return REDIS_OK;
}
