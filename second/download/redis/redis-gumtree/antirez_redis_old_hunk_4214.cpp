    }
}

int main(int argc, char **argv) {
    time_t start;

    initServerConfig();
    if (argc == 2) {
        resetServerSaveParams();
        loadServerConfig(argv[1]);
    } else if (argc > 2) {
