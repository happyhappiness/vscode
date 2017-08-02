archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for %s decompression",
		    self->name)