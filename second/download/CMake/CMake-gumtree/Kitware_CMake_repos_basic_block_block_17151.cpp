{
			archive_strcat(&shar->work, "chown ");
			if (u != NULL)
				shar_quote(&shar->work, u, 1);
			if (g != NULL) {
				archive_strcat(&shar->work, ":");
				shar_quote(&shar->work, g, 1);
			}
			archive_strcat(&shar->work, " ");
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}