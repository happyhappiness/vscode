{
				archive_strcat(&shar->work, "mkdir -p ");
				shar_quote(&shar->work, p, 1);
				archive_strcat(&shar->work,
				    " > /dev/null 2>&1\n");
				shar->last_dir = p;
			}