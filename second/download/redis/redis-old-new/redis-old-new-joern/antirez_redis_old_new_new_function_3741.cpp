void printValid(uint64_t ops, uint64_t bytes) {
    char body[80];
    sprintf(body, "Processed %llu valid opcodes (in %llu bytes)",
        (unsigned long long) ops, (unsigned long long) bytes);
    printCentered(4, 80, body);
}