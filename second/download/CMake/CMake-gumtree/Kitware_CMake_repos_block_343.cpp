{
					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot remove intervening "
					    "symlink %s", path);
					res = ARCHIVE_FAILED;
					break;
				}