void printSkipped(int bytes, int offset) {
    char body[80];
    sprintf(body, "Skipped %d bytes (resuming at 0x%08x)", bytes, offset);
    printCentered(4, 80, body);
}