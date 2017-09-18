		*colon = '\0';
	    }
	    if (strcmp(user, scratch) != 0) {
		putline(ftemp, line);
		continue;
	    }
            else {
                /* We found the user we were looking for, add him to the file.
                 */
                apr_file_printf(errfile, "Updating ");
                putline(ftemp, record);
            }
	}
    }
    if (!found) {
        apr_file_printf(errfile, "Adding ");
        putline(ftemp, record);
    }
    apr_file_printf(errfile, "password for user %s\n", user);
    apr_file_close(fpw);

    /* The temporary file has all the data, just copy it to the new location.
     */
#if defined(OS2) || defined(WIN32)
    str = apr_psprintf(pool, "copy \"%s\" \"%s\"", tn, pwfilename);
#else
    str = apr_psprintf(pool, "cp %s %s", tn, pwfilename);
#endif
    system(str);
    apr_file_close(ftemp);
    return 0;
}
