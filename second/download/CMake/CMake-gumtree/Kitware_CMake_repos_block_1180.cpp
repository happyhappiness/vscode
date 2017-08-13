{
		case AE_IFREG:
			if (archive_entry_size(entry) == 0) {
				/* More portable than "touch." */
				archive_string_sprintf(&shar->work,
				    "test -e \"%s\" || :> \"%s\"\n",
				    shar->quoted_name.s, shar->quoted_name.s);
			} else {
				if (shar->dump) {
					unsigned int mode = archive_entry_mode(entry) & 0777;
					archive_string_sprintf(&shar->work,
					    "uudecode -p > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
					archive_string_sprintf(&shar->work,
					    "begin %o ", mode);
					shar_quote(&shar->work, name, 0);
					archive_strcat(&shar->work, "\n");
				} else {
					archive_string_sprintf(&shar->work,
					    "sed 's/^X//' > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
				}
				shar->has_data = 1;
				shar->end_of_line = 1;
				shar->outpos = 0;
			}
			break;
		case AE_IFDIR:
			archive_string_sprintf(&shar->work,
			    "mkdir -p %s > /dev/null 2>&1\n",
			    shar->quoted_name.s);
			/* Record that we just created this directory. */
			if (shar->last_dir != NULL)
				free(shar->last_dir);

			shar->last_dir = strdup(name);
			/* Trim a trailing '/'. */
			pp = strrchr(shar->last_dir, '/');
			if (pp != NULL && pp[1] == '\0')
				*pp = '\0';
			/*
			 * TODO: Put dir name/mode on a list to be fixed
			 * up at end of archive.
			 */
			break;
		case AE_IFIFO:
			archive_string_sprintf(&shar->work,
			    "mkfifo %s\n", shar->quoted_name.s);
			break;
		case AE_IFCHR:
			archive_string_sprintf(&shar->work,
			    "mknod %s c %ju %ju\n", shar->quoted_name.s,
			    (uintmax_t)archive_entry_rdevmajor(entry),
			    (uintmax_t)archive_entry_rdevminor(entry));
			break;
		case AE_IFBLK:
			archive_string_sprintf(&shar->work,
			    "mknod %s b %ju %ju\n", shar->quoted_name.s,
			    (uintmax_t)archive_entry_rdevmajor(entry),
			    (uintmax_t)archive_entry_rdevminor(entry));
			break;
		default:
			return (ARCHIVE_WARN);
		}