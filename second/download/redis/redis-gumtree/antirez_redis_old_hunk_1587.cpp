
    memset(head, '=', indent);
    memset(tail, '=', width - 2 - indent - strlen(body));
    printf("%s %s %s\n", head, body, tail);
}

static void printValid(uint64_t ops, uint64_t bytes) {
