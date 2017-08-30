	fid = t->max_filesystem_id++;

	if (t->max_filesystem_id > t->allocated_filesytem) {

		size_t s;



		s = t->max_filesystem_id * 2;

		t->filesystem_table = realloc(t->filesystem_table,

		    s * sizeof(*t->filesystem_table));

		if (t->filesystem_table == NULL) {

			archive_set_error(&a->archive, ENOMEM,

			    "Can't allocate tar data");

			return (ARCHIVE_FATAL);

		}

		t->allocated_filesytem = s;

	}

	t->current_filesystem_id = fid;

	t->current_filesystem = &(t->filesystem_table[fid]);

