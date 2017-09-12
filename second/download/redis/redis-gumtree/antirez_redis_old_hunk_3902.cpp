
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        printf("0x%08llx - %s\n", errors.offset[i], errors.error[i]);
    }
}

