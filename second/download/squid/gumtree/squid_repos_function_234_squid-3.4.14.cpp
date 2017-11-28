static int
validate_user_pw(char *username, char *groupname)
{
    struct passwd *p;
    struct group *g;

    if ((p = getpwnam(username)) == NULL) {
        /* Returns an error if user does not exist in the /etc/passwd */
        fprintf(stderr, "ERROR: User does not exist '%s'\n", username);
        return 0;
    } else {
        /* Verify if the this is the primary user group */
        if ((g = getgrgid(p->pw_gid)) != NULL) {
            if ((strcmp(groupname, g->gr_name)) == 0)
                return 1;
        }
    }

    return 0;
}