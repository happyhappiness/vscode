		 * impact.

		 */

		if (lchmod(a->name, mode) != 0) {

			archive_set_error(&a->archive, errno,

			    "Can't set permissions to 0%o", (int)mode);

			r = ARCHIVE_WARN;

		}

#endif

	} else if (!S_ISDIR(a->mode)) {

