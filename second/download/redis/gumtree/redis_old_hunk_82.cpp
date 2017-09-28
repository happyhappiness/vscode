            dbAdd(c->db,c->argv[1],lobj);
        }
        listTypePush(lobj,c->argv[j],where);
        pushed++;
    }
    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
    if (pushed) signalModifiedKey(c->db,c->argv[1]);
    server.dirty += pushed;
}

void lpushCommand(redisClient *c) {
    pushGenericCommand(c,REDIS_HEAD);
}
