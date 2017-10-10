	 * uninteresting.
	 */
	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");

	if (is_null_sha1(sb.final->object.sha1)) {
		o = sb.final->util;
		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb.final_buf_size = o->file.size;
	}
	else {
		o = get_origin(&sb, sb.final, path);
		if (fill_blob_sha1_and_mode(o))
			die("no such path %s in %s", path, final_commit_name);
