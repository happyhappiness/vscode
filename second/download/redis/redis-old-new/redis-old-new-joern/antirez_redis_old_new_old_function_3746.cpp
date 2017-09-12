void printErrorStack(entry *e) {
    unsigned int i;
    char body[64];

    if (e->type == -1) {
        sprintf(body, "Error trace");
    } else if (e->type >= 253) {
        sprintf(body, "Error trace (%s)", types[e->type]);
    } else if (!e->key) {
        sprintf(body, "Error trace (%s: (unknown))", types[e->type]);
    } else {
        char tmp[41];
        strncpy(tmp, e->key, 40);

        /* display truncation at the last 3 chars */
        if (strlen(e->key) > 40) {
            memset(&tmp[37], '.', 3);
        }

        /* display unprintable characters as ? */
        for (i = 0; i < strlen(tmp); i++) {
            if (tmp[i] <= 32) tmp[i] = '?';
        }
        sprintf(body, "Error trace (%s: %s)", types[e->type], tmp);
    }

    printCentered(4, 80, body);

    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        printf("0x%08llx - %s\n", errors.offset[i], errors.error[i]);
    }
}