
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        printf("0x%08lx - %s\n",
            (unsigned long) errors.offset[i], errors.error[i]);
    }
}

