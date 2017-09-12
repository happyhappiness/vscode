
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        printf("0x%08lx - %s\n", errors.offset[i], errors.error[i]);
    }
}

void process() {
    int i, num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
    entry entry;
    processHeader();

