		*colon = '\0';
	    }
	    if (strcmp(user, scratch) != 0) {
		putline(ftemp, line);
		continue;
	    }
	    found++;
	    break;
	}
    }
    if (found) {
	fprintf(stderr, "Updating ");
    }
    else {
	fprintf(stderr, "Adding ");
    }
    fprintf(stderr, "password for user %s\n", user);
    /*
     * Now add the user record we created.
     */
    putline(ftemp, record);
    /*
     * If we're updating an existing file, there may be additional
     * records beyond the one we're updating, so copy them.
     */
    if (! newfile) {
	copy_file(ftemp, fpw);
	fclose(fpw);
    }
    /*
     * The temporary file now contains the information that should be
     * in the actual password file.  Close the open files, re-open them
     * in the appropriate mode, and copy them file to the real one.
     */
    fclose(ftemp);
    fpw = fopen(pwfilename, "w+");
    ftemp = fopen(tempfilename, "r");
    copy_file(fpw, ftemp);
    fclose(fpw);
    fclose(ftemp);
    unlink(tempfilename);
    return 0;
}
