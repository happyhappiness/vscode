{
			iso9660->rr_moved = file;
			file->rr_moved = 1;
			file->rr_moved_has_re_only = 1;
			file->re = 0;
			parent->subdirs--;
		}