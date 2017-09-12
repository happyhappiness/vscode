    }
}

int main(int argc, char **argv) {
#ifdef __linux__
    linuxOvercommitMemoryWarning();
#endif
    
    initServerConfig();
    if (argc == 2) {
        ResetServerSaveParams();
