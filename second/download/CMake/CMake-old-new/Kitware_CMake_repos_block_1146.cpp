{
				/* More portable than "touch." */
				archive_string_sprintf(&shar->work,
				    "test -e \"%s\" || :> \"%s\"\n",
				    shar->quoted_name.s, shar->quoted_name.s);
			}