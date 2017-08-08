{
					archive_string_sprintf(&shar->work,
					    "sed 's/^X//' > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
				}