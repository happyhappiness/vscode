            pubsubUnsubscribePattern(c,c->argv[j],1);
    }
}

void publishCommand(redisClient *c) {
    int receivers = pubsubPublishMessage(c->argv[1],c->argv[2]);
    addReplyLongLong(c,receivers);
}
