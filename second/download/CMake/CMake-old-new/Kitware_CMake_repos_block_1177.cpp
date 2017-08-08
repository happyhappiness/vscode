{
					unsigned int mode = archive_entry_mode(entry) & 0777;
					archive_string_sprintf(&shar->work,
					    "uudecode -p > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
					archive_string_sprintf(&shar->work,
					    "begin %o ", mode);
					shar_quote(&shar->work, name, 0);
					archive_strcat(&shar->work, "\n");
				}