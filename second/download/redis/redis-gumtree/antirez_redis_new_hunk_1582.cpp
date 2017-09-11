    char *key = loadStringObject();
    if (key == NULL) {
        SHIFT_ERROR(offset, "Error reading string object");
        zfree(key);
        return 0;
    }

    if (store != NULL) {
        *store = key;
    } else {
        zfree(key);
    }
    return 1;
}
