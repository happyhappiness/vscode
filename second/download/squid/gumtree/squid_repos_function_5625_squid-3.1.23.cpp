struct group *
getgrnam(char *unused) {
    static struct group grp = {NULL, NULL, 100, NULL};
    return &grp;
}