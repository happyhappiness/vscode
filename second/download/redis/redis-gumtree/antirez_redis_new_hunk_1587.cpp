
    memset(head, '=', indent);
    memset(tail, '=', width - 2 - indent - strlen(body));
    redisLog(REDIS_WARNING, "%s %s %s", head, body, tail);
}

static void printValid(uint64_t ops, uint64_t bytes) {
