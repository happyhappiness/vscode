int
readSecret(const char *filename)
{
    char buf[BUFSIZ];
    char *e = NULL;
    FILE *f;
    char *passwd = NULL;

    if (!(f = fopen(filename, "r"))) {
        fprintf(stderr, PROGRAM_NAME " ERROR: Can not read secret file %s\n", filename);
        return 1;
    }
    if (!fgets(buf, sizeof(buf) - 1, f)) {
        fprintf(stderr, PROGRAM_NAME " ERROR: Secret file %s is empty\n", filename);
        fclose(f);
        return 1;
    }
    /* strip whitespaces on end */
    if ((e = strrchr(buf, '\n')))
        *e = 0;
    if ((e = strrchr(buf, '\r')))
        *e = 0;

    passwd = (char *) calloc(sizeof(char), strlen(buf) + 1);
    if (!passwd) {
        fprintf(stderr, PROGRAM_NAME " ERROR: can not allocate memory\n");
        exit(1);
    }
    strcpy(passwd, buf);
    bindpasswd = passwd;

    fclose(f);

    return 0;
}