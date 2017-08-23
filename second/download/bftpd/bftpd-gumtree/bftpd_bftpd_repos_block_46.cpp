{
	char str[MAX_STRING_LENGTH + 1];
	char *foo;
	int maxusers;
        char *file_auth;   /* if used, points to file used to auth users */
        char *home_directory = NULL;   /* retrieved from auth_file */
        char *anonymous = NULL;
        unsigned long get_maxusers;
        int anon_ok = FALSE;

        str[0] = '\0';     /* avoid garbage in str */
        file_auth = config_getoption("FILE_AUTH");

        if (! file_auth[0] )    /* not using auth file */
        {
           /* check to see if regular authentication is avail */
           anonymous = config_getoption("ANONYMOUS_USER");
           if (! strcasecmp(anonymous, "yes") )
           {
              home_directory = "/";
              anon_ok = TRUE;
           }
           #ifndef NO_GETPWNAM
	   else if (!getpwnam(user)) {
                control_printf(SL_FAILURE, "530 Login incorrect.");
		// exit(0);
                return -1;
           }
           #endif
        }
        /* we are using auth_file */
        else
        {
           home_directory = check_file_password(file_auth, user, password);
           anonymous = config_getoption("ANONYMOUS_USER");
           if (! home_directory)
           {
               if (! strcasecmp(anonymous, "yes") )
                   home_directory = "/";
               else
               {
                  control_printf(SL_FAILURE, "530 Anonymous user not allowed.");
                  //exit(0);
                  return -1;
               }
           }
        }

	if (strncasecmp(foo = config_getoption("DENY_LOGIN"), "no", 2)) {
		if (foo[0] != '\0') {
			if (strncasecmp(foo, "yes", 3))
				control_printf(SL_FAILURE, "530-Server disabled.\r\n421 Reason: %s", foo);
			else
				control_printf(SL_FAILURE, "530 Login incorrect.");
			bftpd_log("Login as user '%s' failed: Server disabled.\n", user);
			exit(0);
		}
	}
	get_maxusers = strtoul(config_getoption("USERLIMIT_GLOBAL"), NULL, 10);
        if (get_maxusers <= INT_MAX)
           maxusers = get_maxusers;
        else
        {
           bftpd_log("Error getting max users for GLOBAL in bftpd_login.\n", 0);
           maxusers = 0;
        }
	if ((maxusers) && (maxusers == bftpdutmp_usercount("*"))) {
		control_printf(SL_FAILURE, "421 There are already %i users logged in.", maxusers);
                bftpd_log("Login as user '%s' failed. Too many users on server.\n", user);
		exit(0);
	}
	get_maxusers = strtoul(config_getoption("USERLIMIT_SINGLEUSER"), NULL, 10);
        if (get_maxusers <= INT_MAX)
           maxusers = get_maxusers;
        else
        {
           bftpd_log("error getting max users (SINGLE USER) in bftpd_login.\n", 0);
           maxusers = 0;
        }
	if ((maxusers) && (maxusers == bftpdutmp_usercount(user))) {
		control_printf(SL_FAILURE, "421 User %s is already logged in %i times.", user, maxusers);
                bftpd_log("Login as user '%s' failed. Already logged in %d times.", maxusers);
		exit(0);
	}

        /* Check to see if we should block mulitple logins from the same machine.
           -- Jesse <slicer69@hotmail.com>
        */
        get_maxusers = strtoul( config_getoption("USERLIMIT_HOST"), NULL, 10);
        if (get_maxusers <= INT_MAX)
           maxusers = get_maxusers;
        else
        {
            bftpd_log("Error getting max users per HOST in bftpd_login.\n", 0);
            maxusers = 0;
        }

        if ( (maxusers) && (maxusers == bftpdutmp_dup_ip_count(remotehostname) ) )
        {
            control_printf(SL_FAILURE, "421 Too many connections from your IP address.");
            bftpd_log("Login as user '%s' failed. Already %d connections from %s.\n", user, maxusers, remotehostname);
            exit(0);
        }
       
        /* disable these checks when logging in via auth file */
        if ( (! file_auth[0] ) && (!anon_ok) )
        {
            #ifndef NO_GETPWNAM
	    if(checkuser() || checkshell()) {
		control_printf(SL_FAILURE, "530 Login incorrect.");
		// exit(0);
                return -1;
	    }
            #endif
        }

        /* do not do this check when we are using auth_file */
        if ( (! file_auth[0] ) && (! anon_ok) )
        {
            #ifndef NO_GETPWNAM
	    if (checkpass(password))
		return 1;
            #endif
        }

	if (strcasecmp((char *) config_getoption("RATIO"), "none")) {
		sscanf((char *) config_getoption("RATIO"), "%i/%i",
			   &ratio_send, &ratio_recv);
	}

        /* do these checks if logging in via normal methods */
        if ( (! file_auth[0]) && (! anon_ok) )
        {
	     strcpy(str, config_getoption("ROOTDIR"));
	     if (!str[0])
		strcpy(str, "%h");
	     replace(str, "%u", userinfo.pw_name, MAX_STRING_LENGTH);
	     replace(str, "%h", userinfo.pw_dir, MAX_STRING_LENGTH);
	     if (!strcasecmp(config_getoption("RESOLVE_UIDS"), "yes")) 
             {
		passwdfile = fopen("/etc/passwd", "r");
		groupfile = fopen("/etc/group", "r");
	     } 

	setgid(userinfo.pw_gid);
	initgroups(userinfo.pw_name, userinfo.pw_gid);
	if (strcasecmp(config_getoption("DO_CHROOT"), "no")) {
		if (chroot(str)) {
			control_printf(SL_FAILURE, "421 Unable to change root directory.\r\n%s.",
					strerror(errno));
			exit(0);
		}
		if (bftpd_setuid(userinfo.pw_uid)) {
			control_printf(SL_FAILURE, "421 Unable to change uid.\r\n");
			exit(0);
		}
		if (chdir("/")) {
			control_printf(SL_FAILURE, "421 Unable to change working directory.\r\n%s.",
					 strerror(errno));
			exit(0);
		}
	} else {
		if (bftpd_setuid(userinfo.pw_uid)) {
			control_printf(SL_FAILURE, "421 Unable to change uid.\r\n");
			exit(0);
		}
		if (chdir(str)) {
			control_printf(SL_FAILURE, "230 Couldn't change cwd to '%s': %s.\r\n", str,
					 strerror(errno));
			chdir("/");
		}
	}

        }   /* end of if we are using regular authentication methods */

        /* perhaps we are using anonymous logins, but not file_auth? */
        else if ( (! file_auth[0]) && (anon_ok) )
        {
          strcpy(str, config_getoption("ROOTDIR"));
          if (! str[0])
             str[0] = '/';
          replace(str, "%h", home_directory, MAX_STRING_LENGTH);
          replace(str, "%u", user, MAX_STRING_LENGTH);
          /* should we chroot? */
          if (! strcasecmp(config_getoption("DO_CHROOT"), "yes") )
          {
             if ( chroot(str) )
             {
                 control_printf(SL_FAILURE, "421 Unable to change root directory.\r\n");
                 exit(0);
             }
             if ( chdir("/") )
             {
                 control_printf(SL_FAILURE, "421 Unable to change working directory.\r\n");
                 exit(0);
             }
          } 
        
        }        /* end of using anonymous login */
        else     /* we are using file authentication */
        {
            /* get home directory */
	    strcpy(str, config_getoption("ROOTDIR"));
            if (! str[0])
                strcpy(str, "%h");
	    replace(str, "%h", home_directory, MAX_STRING_LENGTH);
            replace(str, "%u", user, MAX_STRING_LENGTH);

            /* see if we should change root */
            if (! strcasecmp(config_getoption("DO_CHROOT"), "yes"))
            {
                if ( chroot(home_directory) )
                {
                    control_printf(SL_FAILURE, "421 Unable to change root directory.\r\n");
                    exit(0);
                }
                if ( chdir("/") )
                {
                    control_printf(SL_FAILURE, "421 Unable to change working directory.\r\n");
                    exit(0);
                }
            }
               
        }      /* end of using file auth */

        new_umask();
	/* print_file(230, config_getoption("MOTD_USER")); */
        strcpy(str, config_getoption("MOTD_USER"));
        /* Allow user specific path to MOTD file. */
        replace(str, "%h", home_directory, MAX_STRING_LENGTH);
        replace(str, "%u", user, MAX_STRING_LENGTH);
        print_file(230, str);

	control_printf(SL_SUCCESS, "230 User logged in.");
#ifdef HAVE_UTMP_H
	bftpd_logwtmp(1);
#endif
        bftpdutmp_log(1);
	bftpd_log("Successfully logged in as user '%s'.\n", user);
        if (config_getoption("AUTO_CHDIR")[0])
            chdir(config_getoption("AUTO_CHDIR"));

	state = STATE_AUTHENTICATED;
	bftpd_cwd_init();

        /* a little clean up before we go */
        if ( (home_directory) && ( strcmp(home_directory, "/" ) ) )
            free(home_directory);
           
	return 0;
}