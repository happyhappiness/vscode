	}

    }

    if (!found) {

	printf("Adding user %s\n", user);

	add_password(user, tfp);

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

    exit(0);

}

-- apache_1.3.0/src/support/logresolve.c	1998-05-28 19:23:13.000000000 +0800

