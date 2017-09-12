void printValid(int ops, int bytes) {
    char body[80];
    sprintf(body, "Processed %d valid opcodes (in %d bytes)", ops, bytes);
    printCentered(4, 80, body);
}