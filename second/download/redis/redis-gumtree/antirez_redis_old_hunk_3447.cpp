    redisAsyncDisconnect(c);
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
}

int main (int argc, char **argv) {
