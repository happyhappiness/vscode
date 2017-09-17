    if (!found) {
	printf("Adding user %s in realm %s\n", user, realm);
	add_password(user, realm, tfp);
    }
    fclose(f);
    fclose(tfp);
#if defined(__EMX__) || defined(WIN32)
    sprintf(command, "copy \"%s\" \"%s\"", tn, argv[1]);
#else
    sprintf(command, "cp %s %s", tn, argv[1]);
#endif
    system(command);
    unlink(tn);
-- apache_1.3.1/src/support/rotatelogs.c	1998-07-13 19:32:58.000000000 +0800
