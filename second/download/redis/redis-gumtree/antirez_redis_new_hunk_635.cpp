    evalGenericCommand(c,1);
}

void scriptCommand(client *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
