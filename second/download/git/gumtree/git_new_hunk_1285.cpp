	if (status != Z_STREAM_END || stream.total_out != obj->size)
		die(_("serious inflate inconsistency"));

	git_inflate_end(&stream);
	free(inbuf);
	if (consume) {
		FREE_AND_NULL(data);
	}
	return data;
}

static void *get_data_from_pack(struct object_entry *obj)
{
