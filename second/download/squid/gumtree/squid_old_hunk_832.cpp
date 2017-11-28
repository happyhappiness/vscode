                      idle, (100.0 * idle / count));

    if (readers || writers) {
        const int locked = readers + writers;
        storeAppendPrintf(&e, "Readers:         %9d %6.2f%%\n",
                          readers, (100.0 * readers / locked));
        storeAppendPrintf(&e, "Writers:         %9d %6.2f%%\n",
                          writers, (100.0 * writers / locked));
    }
}
