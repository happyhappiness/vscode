
    if (reply == NULL) return 1;
    if (!quiet)
        printf("%s", reply);
    sdsfree(reply);
    return 0;
}
