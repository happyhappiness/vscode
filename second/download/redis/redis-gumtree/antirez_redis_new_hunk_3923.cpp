    }
}

int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    REDIS_NOTUSED(eventLoop);
    REDIS_NOTUSED(id);
    REDIS_NOTUSED(clientData);

    float dt = (float)(mstime()-config.start)/1000.0;
    float rps = (float)config.donerequests/dt;
    printf("%s: %.2f\r", config.title, rps);
    fflush(stdout);
    return 250; /* every 250ms */
}

int main(int argc, char **argv) {
    client c;

