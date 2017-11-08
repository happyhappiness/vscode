int initgroups(const char *name, gid_t basegid)
{
    /* QNX and MPE do not appear to support supplementary groups. */
    return 0;
}