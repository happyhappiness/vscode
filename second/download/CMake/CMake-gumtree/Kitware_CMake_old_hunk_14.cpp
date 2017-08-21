				if (unlink(head)) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not remove symlink %s",
					    path);
					res = ARCHIVE_FAILED;
					break;
