{
		archive_strcat(&shar->work, "ln -f ");
		shar_quote(&shar->work, linkname, 1);
		archive_string_sprintf(&shar->work, " %s\n",
		    shar->quoted_name.s);
	}