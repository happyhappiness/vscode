
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        serverLog(LL_WARNING, "0x%08lx - %s",
            (unsigned long) errors.offset[i], errors.error[i]);
    }
}
