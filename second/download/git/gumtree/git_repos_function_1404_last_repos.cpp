static int three_way_merge(struct image *image,
			   char *path,
			   const struct object_id *base,
			   const struct object_id *ours,
			   const struct object_id *theirs)
{
	mmfile_t base_file, our_file, their_file;
	mmbuffer_t result = { NULL };
	int status;

	read_mmblob(&base_file, base);
	read_mmblob(&our_file, ours);
	read_mmblob(&their_file, theirs);
	status = ll_merge(&result, path,
			  &base_file, "base",
			  &our_file, "ours",
			  &their_file, "theirs", NULL);
	free(base_file.ptr);
	free(our_file.ptr);
	free(their_file.ptr);
	if (status < 0 || !result.ptr) {
		free(result.ptr);
		return -1;
	}
	clear_image(image);
	image->buf = result.ptr;
	image->len = result.size;

	return status;
}