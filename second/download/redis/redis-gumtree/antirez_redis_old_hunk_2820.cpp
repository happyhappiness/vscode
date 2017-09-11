    redisAsyncDisconnect(c);
}

void connectCallback(const redisAsyncContext *c) {
    ((void)c);
    printf("connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    printf("disconnected...\n");
    aeStop(loop);
}

int main (int argc, char **argv) {
