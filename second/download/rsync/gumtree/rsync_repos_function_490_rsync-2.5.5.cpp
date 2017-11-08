const char * poptGetArg(poptContext con) {
    if (con->numLeftovers == con->nextLeftover) return NULL;
    return con->leftovers[con->nextLeftover++];
}