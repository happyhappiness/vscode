		    (parent->re || parent->re_descendant))
			file->re_descendant = 1;
		if (file->cl_offset) {
			struct file_info *r;

			if (parent == NULL || parent->parent == NULL) {
				archive_set_error(&a->archive,
