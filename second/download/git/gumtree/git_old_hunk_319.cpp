	if (!o->file.ptr) {
		enum object_type type;
		unsigned long file_size;

		num_read_blob++;
		if (DIFF_OPT_TST(opt, ALLOW_TEXTCONV) &&
		    textconv_object(o->path, o->mode, o->blob_sha1, 1, &file->ptr, &file_size))
			;
		else
			file->ptr = read_sha1_file(o->blob_sha1, &type, &file_size);
		file->size = file_size;

		if (!file->ptr)
			die("Cannot read blob %s for path %s",
			    sha1_to_hex(o->blob_sha1),
			    o->path);
		o->file = *file;
	}
	else
		*file = o->file;
}
