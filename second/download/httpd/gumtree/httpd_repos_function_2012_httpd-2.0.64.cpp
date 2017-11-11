int initgroups(const char *name, gid_t basegid)
{
#if defined(QNX) || defined(MPE) || defined(BEOS) || defined(_OSD_POSIX) || defined(TPF) || defined(__TANDEM) || defined(OS2) || defined(WIN32) || defined(NETWARE)
/* QNX, MPE and BeOS do not appear to support supplementary groups. */
    return 0;
#else /* ndef QNX */
    gid_t groups[NGROUPS_MAX];
    struct group *g;
    int index = 0;

    setgrent();

    groups[index++] = basegid;

    while (index < NGROUPS_MAX && ((g = getgrent()) != NULL)) {
        if (g->gr_gid != basegid) {
            char **names;

            for (names = g->gr_mem; *names != NULL; ++names) {
                if (!strcmp(*names, name))
                    groups[index++] = g->gr_gid;
            }
        }
    }

    endgrent();

    return setgroups(index, groups);
#endif /* def QNX */
}