
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        printf("0x%08llx - %s\n", errors.offset[i], errors.error[i]);
    }
}

void process() {
    uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
    entry entry;
    processHeader();

