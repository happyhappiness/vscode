slowlogEntry *slowlogCreateEntry(robj **argv, int argc, long long duration) {
    slowlogEntry *se = zmalloc(sizeof(*se));
    int j;

    se->argc = argc;
    se->argv = zmalloc(sizeof(robj*)*argc);
    for (j = 0; j < argc; j++) {
        se->argv[j] = argv[j];
        incrRefCount(argv[j]);
    }
    se->time = time(NULL);
    se->duration = duration;
    se->id = server.slowlog_entry_id++;
    return se;
}