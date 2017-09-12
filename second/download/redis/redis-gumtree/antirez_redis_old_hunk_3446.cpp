    redisAsyncDisconnect(c);
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
}

int main (int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    struct ev_loop *loop = ev_default_loop(0);

    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
