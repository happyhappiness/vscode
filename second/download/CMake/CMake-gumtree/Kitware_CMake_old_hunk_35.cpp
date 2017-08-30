				 * with the deep-directory editing.

				 */

				fsobj_error(a_eno, a_estr, errno,

				    "Could not stat %s", path);

				res = ARCHIVE_FAILED;

				break;

			}

