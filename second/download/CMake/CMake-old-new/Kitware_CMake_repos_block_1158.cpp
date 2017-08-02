{
			archive_string_sprintf(&shar->work, "chflags %s ", p);
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}