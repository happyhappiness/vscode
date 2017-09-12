    }
}

static void version() {
    printf("Redis server version %s\n", REDIS_VERSION);
    exit(0);
}

int main(int argc, char **argv) {
    time_t start;

    initServerConfig();
    if (argc == 2) {
        if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)) {
            version();
        }
        resetServerSaveParams();
        loadServerConfig(argv[1]);
    } else if (argc > 2) {
