int initgroups(const char *name, gid_t basegid)
{
#if HAVE_SETGROUPS
#ifndef NGROUPS_MAX
#define NGROUPS_MAX 16
#endif

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

#else

    return 0;

#endif /* def HAVE_SETGROUPS */
}