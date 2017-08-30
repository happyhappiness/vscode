			 * Sanity check: cl_offset does not point at its

			 * the parents or itself.

			 */

			for (r = parent; r; r = r->parent) {

				if (r->offset == file->cl_offset) {

					archive_set_error(&a->archive,

					    ARCHIVE_ERRNO_MISC,

					    "Invalid Rockridge CL");
