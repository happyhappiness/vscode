{
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not chdir %s", path);
					res = (ARCHIVE_FATAL);
					break;
				}