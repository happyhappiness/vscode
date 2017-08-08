{
				/*
				 * Treat any other error as fatal - best to be
				 * paranoid here.
				 * Note: This effectively disables deep
				 * directory support when security checks are
				 * enabled. Otherwise, very long pathnames that
				 * trigger an error here could evade the
				 * sandbox.
				 * TODO: We could do better, but it would
				 * probably require merging the symlink checks
				 * with the deep-directory editing.
				 */
				fsobj_error(a_eno, a_estr, errno,
				    "Could not stat %s", path);
				res = ARCHIVE_FAILED;
				break;
			}