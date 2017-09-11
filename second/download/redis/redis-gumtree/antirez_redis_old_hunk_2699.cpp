void process() {
    uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
    entry entry;
    processHeader();

    level = 1;
    while(positions[0].offset < positions[0].size) {
