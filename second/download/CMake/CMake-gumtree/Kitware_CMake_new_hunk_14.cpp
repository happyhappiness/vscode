				if (chdir(head) != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not chdir ", path);
					res = (ARCHIVE_FATAL);
					break;
				}
