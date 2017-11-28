struct passwd *
getpwnam(char *unused) {
    static struct passwd pwd = {NULL, NULL, 100, 100, NULL, NULL, NULL};
    return &pwd;
}