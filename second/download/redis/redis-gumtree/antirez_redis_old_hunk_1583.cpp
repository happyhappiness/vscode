    double *val = loadDoubleValue();
    if (val == NULL) {
        SHIFT_ERROR(offset, "Error reading double value");
        free(val);
        return 0;
    }

    if (store != NULL) {
        *store = val;
    } else {
        free(val);
    }
    return 1;
}
