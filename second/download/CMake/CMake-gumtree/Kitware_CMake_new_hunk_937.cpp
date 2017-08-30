	if ((zip_entry->mode & AE_IFMT) == AE_IFLNK) {

		unsigned char *symname = NULL;

		size_t symsize = 0;



		/*

		 * Symbolic-name is recorded as its contents. We have to

		 * read the contents at this time.

		 */

		while (zip->entry_bytes_remaining > 0) {

			const void *buff;

			unsigned char *mem;

			size_t size;

			int64_t offset;



			r = archive_read_format_7zip_read_data(a, &buff,

				&size, &offset);

			if (r < ARCHIVE_WARN) {

				free(symname);

				return (r);

			}

			mem = realloc(symname, symsize + size + 1);

			if (mem == NULL) {

				free(symname);

				archive_set_error(&a->archive, ENOMEM,

				    "Can't allocate memory for Symname");

				return (ARCHIVE_FATAL);

			}

			symname = mem;

			memcpy(symname+symsize, buff, size);

			symsize += size;

		}

