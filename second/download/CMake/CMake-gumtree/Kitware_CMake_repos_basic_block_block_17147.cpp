{
			/* Finish sed-encoded data:  ensure last line ends. */
			if (!shar->end_of_line)
				archive_strappend_char(&shar->work, '\n');
			archive_strcat(&shar->work, "SHAR_END\n");
		}