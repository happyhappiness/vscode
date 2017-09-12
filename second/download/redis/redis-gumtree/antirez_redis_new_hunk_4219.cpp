    }
}

static void usage() {
    fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
    exit(1);
}

int main(int argc, char **argv) {
    time_t start;

    initServerConfig();
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            usage();
        }
        resetServerSaveParams();
        loadServerConfig(argv[1]);
    } else if ((argc > 2)) {
        usage();
    } else {
        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
    }
