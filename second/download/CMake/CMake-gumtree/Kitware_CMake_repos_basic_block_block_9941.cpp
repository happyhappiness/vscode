{
		archive_entry_sparse_next(entry, &offset, &length);
		aligned = align_num_per_sector(t, offset);
		if (aligned != offset) {
			aligned -= t->current_filesystem->bytesPerSector;
			length += offset - aligned;
		}
		t->sparse_list[i].offset = aligned;
		aligned = align_num_per_sector(t, length);
		t->sparse_list[i].length = aligned;
	}