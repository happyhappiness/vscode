		 * If we can't look up the real name, warn and return

		 * the entry with the wrong name.

		 */

		if (ar->strtab == NULL || number >= ar->strtab_size) {

			archive_set_error(&a->archive, EINVAL,

			    "Can't find long filename for GNU/SVR4 archive entry");

			archive_entry_copy_pathname(entry, filename);

