(i = 0;  acmd->argv[i] != NULL; i++) {
		if (i == 0) {
			const char *p, *sp;

			if ((p = strchr(acmd->argv[i], '/')) != NULL ||
			    (p = strchr(acmd->argv[i], '\\')) != NULL)
				p++;
			else
				p = acmd->argv[i];
			if ((sp = strchr(p, ' ')) != NULL)
				archive_strappend_char(&cmdline, '"');
			archive_strcat(&cmdline, p);
			if (sp != NULL)
				archive_strappend_char(&cmdline, '"');
		} else {
			archive_strappend_char(&cmdline, ' ');
			archive_strcat(&cmdline, acmd->argv[i]);
		}
	}