    REDIS_NOTUSED(id);
    REDIS_NOTUSED(clientData);

    float dt = (float)(mstime()-config.start)/1000.0;
    float rps = (float)config.requests_finished/dt;
    printf("%s: %.2f\r", config.title, rps);
    fflush(stdout);
    return 250; /* every 250ms */
}

int main(int argc, const char **argv) {
    int i;
    char *data, *cmd;
