
    if (reply == NULL) return 1;
    if (!quiet)
        printf("%s\n", reply);
    sdsfree(reply);
    return 0;
}
