static char *get_dbm_grp(request_rec *r, char *user, char *auth_dbmgrpfile, 
                         char *dbtype)
{
    char *grp_data = get_dbm_pw(r, user, auth_dbmgrpfile,dbtype);
    char *grp_colon;
    char *grp_colon2;

    if (grp_data == NULL)
        return NULL;

    if ((grp_colon = strchr(grp_data, ':')) != NULL) {
        grp_colon2 = strchr(++grp_colon, ':');
        if (grp_colon2)
            *grp_colon2 = '\0';
        return grp_colon;
    }
    return grp_data;
}