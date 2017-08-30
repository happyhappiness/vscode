	 * Check coder types.

	 */

	for (i = 0; i < folder->numCoders; i++) {

		if (folder->coders[i].codec == _7Z_CRYPTO) {

			archive_set_error(&(a->archive),

			    ARCHIVE_ERRNO_MISC,

			    "The %s is encrypted, "

			    "but currently not supported", cname);

			return (ARCHIVE_FATAL);

		}

		if (folder->coders[i].codec == _7Z_X86_BCJ2)

			found_bcj2++;

	}

	if ((folder->numCoders > 2 && !found_bcj2) || found_bcj2 > 1) {

		archive_set_error(&(a->archive),

		    ARCHIVE_ERRNO_MISC,
