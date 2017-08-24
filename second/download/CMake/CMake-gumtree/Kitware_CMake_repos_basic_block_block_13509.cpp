{
				struct archive_string s;
				archive_string_init(&s);
				archive_strcat(&s, cp);
				archive_strappend_char(&s, '/');
				archive_entry_set_pathname(entry, s.s);
				archive_string_free(&s);
			}