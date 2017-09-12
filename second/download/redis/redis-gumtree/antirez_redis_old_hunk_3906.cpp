    printf("%s %s %s\n", head, body, tail);
}

void printValid(int ops, int bytes) {
    char body[80];
    sprintf(body, "Processed %d valid opcodes (in %d bytes)", ops, bytes);
    printCentered(4, 80, body);
}

void printSkipped(int bytes, int offset) {
    char body[80];
    sprintf(body, "Skipped %d bytes (resuming at 0x%08x)", bytes, offset);
    printCentered(4, 80, body);
}

