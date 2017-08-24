(r != ARCHIVE_OK) {
			archive_set_error(&a->archive, errno,
			    "Couldn't translate access ACLs");
			return (r);
		}