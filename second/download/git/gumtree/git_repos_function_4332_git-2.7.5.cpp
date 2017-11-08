static void emit_porcelain_details(struct origin *suspect, int repeat)
{
	if (emit_one_suspect_detail(suspect, repeat) ||
	    (suspect->commit->object.flags & MORE_THAN_ONE_PATH))
		write_filename_info(suspect->path);
}