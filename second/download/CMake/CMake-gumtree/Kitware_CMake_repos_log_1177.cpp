archive_string_sprintf(&shar->work,
					    "uudecode -p > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);