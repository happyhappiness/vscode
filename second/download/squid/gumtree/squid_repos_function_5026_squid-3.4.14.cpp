char *
Fs::Ufs::UFSSwapDir::logFile(char const *ext) const
{
    LOCAL_ARRAY(char, lpath, MAXPATHLEN);
    LOCAL_ARRAY(char, pathtmp, MAXPATHLEN);
    LOCAL_ARRAY(char, digit, 32);
    char *pathtmp2;

    if (Config.Log.swap) {
        xstrncpy(pathtmp, path, MAXPATHLEN - 64);
        pathtmp2 = pathtmp;

        while ((pathtmp2 = strchr(pathtmp2, '/')) != NULL)
            *pathtmp2 = '.';

        while (strlen(pathtmp) && pathtmp[strlen(pathtmp) - 1] == '.')
            pathtmp[strlen(pathtmp) - 1] = '\0';

        for (pathtmp2 = pathtmp; *pathtmp2 == '.'; ++pathtmp2);
        snprintf(lpath, MAXPATHLEN - 64, Config.Log.swap, pathtmp2);

        if (strncmp(lpath, Config.Log.swap, MAXPATHLEN - 64) == 0) {
            strcat(lpath, ".");
            snprintf(digit, 32, "%02d", index);
            strncat(lpath, digit, 3);
        }
    } else {
        xstrncpy(lpath, path, MAXPATHLEN - 64);
        strcat(lpath, "/swap.state");
    }

    if (ext)
        strncat(lpath, ext, 16);

    return lpath;
}