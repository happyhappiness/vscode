			 * Sanity check: cl_offset does not point at its

			 * the parents or itself.

			 */

			for (p = parent; p; p = p->parent) {

				if (p->offset == file->cl_offset) {

					archive_set_error(&a->archive,

					    ARCHIVE_ERRNO_MISC,

					    "Invalid Rockridge CL");
