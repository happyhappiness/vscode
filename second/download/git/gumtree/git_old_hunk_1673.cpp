	/*
	 * If we have bottom, this will mark the ancestors of the
	 * bottom commits we would reach while traversing as
	 * uninteresting.
	 */
	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");

	if (is_null_sha1(sb.final->object.sha1)) {
		o = sb.final->util;
		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb.final_buf_size = o->file.size;
	}
