void printSkipped(uint64_t bytes, uint64_t offset) {
    char body[80];
    sprintf(body, "Skipped %llu bytes (resuming at 0x%08llx)", bytes, offset);
    printCentered(4, 80, body);
}