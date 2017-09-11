    double *val = loadDoubleValue();
    if (val == NULL) {
        SHIFT_ERROR(offset, "Error reading double value");
        zfree(val);
        return 0;
    }

    if (store != NULL) {
        *store = val;
    } else {
        zfree(val);
    }
    return 1;
}
