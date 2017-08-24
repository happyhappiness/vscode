(strcmp(p, ".") == 0) {
				/* Don't try to "mkdir ." */
				free(p);
			} else if (shar->last_dir == NULL) {
				archive_strcat(&shar->work, "mkdir -p ");
				shar_quote(&shar->work, p, 1);
				archive_strcat(&shar->work,
				    " > /dev/null 2>&1\n");
				shar->last_dir = p;
			} else if (strcmp(p, shar->last_dir) == 0) {
				/* We've already created this exact dir. */
				free(p);
			} else if (strlen(p) < strlen(shar->last_dir) &&
			    strncmp(p, shar->last_dir, strlen(p)) == 0) {
				/* We've already created a subdir. */
				free(p);
			} else {
				archive_strcat(&shar->work, "mkdir -p ");
				shar_quote(&shar->work, p, 1);
				archive_strcat(&shar->work,
				    " > /dev/null 2>&1\n");
				shar->last_dir = p;
			}