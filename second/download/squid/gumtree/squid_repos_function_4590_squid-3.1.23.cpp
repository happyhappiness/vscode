static char *
storeCossDirSwapLogFile(SwapDir * sd, const char *ext)
{
    LOCAL_ARRAY(char, path, SQUID_MAXPATHLEN);
    LOCAL_ARRAY(char, pathtmp, SQUID_MAXPATHLEN);
    LOCAL_ARRAY(char, digit, 32);
    char *pathtmp2;

    if (Config.Log.swap) {
        xstrncpy(pathtmp, sd->path, SQUID_MAXPATHLEN - 64);
        pathtmp2 = pathtmp;

        while ((pathtmp2 = strchr(pathtmp2, '/')) != NULL)
            *pathtmp2 = '.';

        while (strlen(pathtmp) && pathtmp[strlen(pathtmp) - 1] == '.')
            pathtmp[strlen(pathtmp) - 1] = '\0';

        for (pathtmp2 = pathtmp; *pathtmp2 == '.'; pathtmp2++);
        snprintf(path, SQUID_MAXPATHLEN - 64, Config.Log.swap, pathtmp2);

        if (strncmp(path, Config.Log.swap, SQUID_MAXPATHLEN - 64) == 0) {
            strcat(path, ".");
            snprintf(digit, 32, "%02d", sd->index);
            strncat(path, digit, 3);
        }
    } else {
        xstrncpy(path, sd->path, SQUID_MAXPATHLEN - 64);
        strcat(path, "/swap.state");
    }

    if (ext)
        strncat(path, ext, 16);

    return path;
}