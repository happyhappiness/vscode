    char line[1024];
    size_t bytes = 0;
    int flen = strlen(field);

    if (pid == -1) {
        FILE *fp = fopen("/proc/self/smaps","r");
    } else {
        char filename[128];
        snprintf(filename,sizeof(filename),"/proc/%ld/smaps",pid);
        FILE *fp = fopen(filename,"r");
    }

    if (!fp) return 0;
