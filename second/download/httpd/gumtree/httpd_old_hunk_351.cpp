	getword(x, l, ':');
	if (strcmp(user, w) || strcmp(realm, x)) {
	    putline(tfp, line);
	    continue;
	}
	else {
	    printf("Changing password for user %s in realm %s\n", user, realm);
	    add_password(user, realm, tfp);
	    found = 1;
	}
    }
    if (!found) {
	printf("Adding user %s in realm %s\n", user, realm);
	add_password(user, realm, tfp);
    }
    apr_file_close(f);
#if defined(OS2) || defined(WIN32)
    sprintf(command, "copy \"%s\" \"%s\"", tn, argv[1]);
#else
    sprintf(command, "cp %s %s", tn, argv[1]);
#endif
    system(command);
    apr_file_close(tfp);
    return 0;
}
