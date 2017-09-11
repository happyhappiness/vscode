    for(i=0;i<TYPE_NONE; i++) {
        maxkeys[i] = sdsempty();
        if(!maxkeys[i]) {
            fprintf(stderr, "Failed to allocate memory for largest key names!");
            exit(1);
        }
    }
