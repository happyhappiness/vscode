{
			t->sparse_list_size = 0;
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate data");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}