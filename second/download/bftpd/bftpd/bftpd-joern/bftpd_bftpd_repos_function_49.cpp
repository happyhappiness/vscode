void config_init()
{
	FILE *configfile;
	char *str;
    struct group_of_users *grp = NULL;
    struct user *usr = NULL;
    config_global.options = NULL;
    config_global.directories = NULL;
	if (!configpath)
		return;
	configfile = fopen(configpath, "r");
	if (!configfile) {
		control_printf(SL_FAILURE, "421 Unable to open configuration file.");
		exit(1);
	}
	while ((str = config_read_line(configfile))) {
		if (strchr(str, '{')) {
            replace(str, " {", "{", MAX_STRING_LENGTH);
            replace(str, "{ ", "{", MAX_STRING_LENGTH);
            replace(str, " }", "}", MAX_STRING_LENGTH);
            replace(str, "} ", "}", MAX_STRING_LENGTH);
            if (!strcasecmp(str, "global{\n")) {
                create_options(configfile, &(config_global.options), &(config_global.directories));
            } else if (strstr(str, "user ") == str) {
                if (usr) {
                    usr = usr->next = malloc(sizeof(struct user));
                } else {
                    config_users = usr = malloc(sizeof(struct user));
                }
                /* avoid memory errors */
                if (! usr)
                {
                    fclose(configfile);
                    control_printf(SL_FAILURE, "421 Memory error while reading config file.");
                    return;
                }

                usr->name = strdup(str + 5);
                if (! usr->name )
                {
                   fclose(configfile);
                   control_printf(SL_FAILURE, "421 Memory error while handling config file.");
                   exit(1);
                }
                *strchr(usr->name, '{') = 0;
                create_options(configfile, &(usr->options), &(usr->directories));
            } else if (strstr(str, "group ") == str) {
                if (grp) {
                    grp = grp->next = malloc(sizeof(struct group_of_users));
                } else {
                    config_groups = grp = malloc(sizeof(struct group_of_users));
                }
                if (! grp)
                {
                    fclose(configfile);
                    control_printf(SL_FAILURE, "421 Memory error while handling config file.");
                    exit(1);
                }
                cutto(str, 6);
                *strchr(str, '{') = 0;
                grp->users = NULL;
                grp->next = NULL;
                grp->temp_members = strdup(str);
                create_options(configfile, &(grp->options), &(grp->directories));
            }
		}
	}
	fclose(configfile);
}