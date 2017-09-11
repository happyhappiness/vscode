
    switch(e->type) {
    case REDIS_STRING:
        if (!processStringObject(NULL)) {
            SHIFT_ERROR(offset, "Error reading entry value");
            return 0;
