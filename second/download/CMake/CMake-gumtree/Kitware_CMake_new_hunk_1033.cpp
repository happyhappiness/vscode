	fid = t->max_filesystem_id++;

	if (t->max_filesystem_id > t->allocated_filesytem) {

		size_t s;

		void *p;



		s = t->max_filesystem_id * 2;

		p = realloc(t->filesystem_table,

			s * sizeof(*t->filesystem_table));

		if (p == NULL) {

			archive_set_error(&a->archive, ENOMEM,

			    "Can't allocate tar data");

			return (ARCHIVE_FATAL);

		}

		t->filesystem_table = (struct filesystem *)p;

		t->allocated_filesytem = (int)s;

	}

	t->current_filesystem_id = fid;

	t->current_filesystem = &(t->filesystem_table[fid]);

