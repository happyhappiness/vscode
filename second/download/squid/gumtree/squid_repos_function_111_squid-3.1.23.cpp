static int
validate_user_gr(char *username, char *groupname)
{
    /*
     * Verify if the user belongs to groupname as listed in the
     * /etc/group file
     */
    struct group *g;

    if ((g = getgrnam(groupname)) == NULL) {
        fprintf(stderr, "helper: Group does not exist '%s'\n",
                groupname);
        return 0;
    } else {
        while (*(g->gr_mem) != NULL) {
            if (strcmp(*((g->gr_mem)++), username) == 0) {
                return 1;
            }
        }
    }
    return 0;
}