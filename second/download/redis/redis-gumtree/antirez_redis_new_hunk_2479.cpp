
        start_vect[regions] = start_addr;
        size_vect[regions] = size;
        printf("Testing %lx %lu\n", (unsigned long) start_vect[regions],
                                    (unsigned long) size_vect[regions]);
        regions++;
    }

