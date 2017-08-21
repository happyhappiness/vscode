					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot extract through "
					    "symlink ", path);
					res = ARCHIVE_FAILED;
					break;
				}
			} else {
				tail[0] = c;
				fsobj_error(a_eno, a_estr, 0,
				    "Cannot extract through symlink ", path);
				res = ARCHIVE_FAILED;
				break;
			}
