int main(int argc, char **argv)
{
    int i, ver;
    DIR *d;
    struct dirent *e;
    const char *s;
    FILE *fp;
    char path[FILENAME_MAX + 1];
    char line[1035];
    time_t date, lmod, expire;
    unsigned int len;
    struct tm ts;
    char sdate[30], slmod[30], sexpire[30];
    const char time_format[] = "%e %b %Y %R";

    if (argc != 2) {
        printf("Usage: cls directory\n");
        exit(0);
    }

    d = opendir(argv[1]);
    if (d == NULL) {
        perror("opendir");
        exit(1);
    }

    for (;;) {
        e = readdir(d);
        if (e == NULL)
            break;
        s = e->d_name;
        if (s[0] == '.' || s[0] == '#')
            continue;
        sprintf(path, "%s/%s", argv[1], s);
        fp = fopen(path, "r");
        if (fp == NULL) {
            perror("fopen");
            continue;
        }
        if (fgets(line, 1034, fp) == NULL) {
            perror("fgets");
            fclose(fp);
            continue;
        }
        if (!checkmask(line, "&&&&&&&& &&&&&&&& &&&&&&&& &&&&&&&& &&&&&&&&\n")) {
            fprintf(stderr, "Bad cache file\n");
            fclose(fp);
            continue;
        }
        date = hex2sec(line);
        lmod = hex2sec(line + 9);
        expire = hex2sec(line + 18);
        ver = hex2sec(line + 27);
        len = hex2sec(line + 35);
        if (fgets(line, 1034, fp) == NULL) {
            perror("fgets");
            fclose(fp);
            continue;
        }
        fclose(fp);
        i = strlen(line);
        if (strncmp(line, "X-URL: ", 7) != 0 || line[i - 1] != '\n') {
            fprintf(stderr, "Bad cache file\n");
            continue;
        }
        line[i - 1] = '\0';
        if (date != -1) {
            ts = *gmtime(&date);
            strftime(sdate, 30, time_format, &ts);
        }
        else
            strcpy(sdate, "-");

        if (lmod != -1) {
            ts = *gmtime(&lmod);
            strftime(slmod, 30, time_format, &ts);
        }
        else
            strcpy(slmod, "-");

        if (expire != -1) {
            ts = *gmtime(&expire);
            strftime(sexpire, 30, time_format, &ts);
        }
        else
            strcpy(sexpire, "-");

        printf("%s: %d; %s  %s  %s\n", line + 7, ver, sdate, slmod, sexpire);
    }

    closedir(d);
    return 0;
}