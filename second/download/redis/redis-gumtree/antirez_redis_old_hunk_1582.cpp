    char *key = loadStringObject();
    if (key == NULL) {
        SHIFT_ERROR(offset, "Error reading string object");
        free(key);
        return 0;
    }

    if (store != NULL) {
        *store = key;
    } else {
        free(key);
    }
    return 1;
}
