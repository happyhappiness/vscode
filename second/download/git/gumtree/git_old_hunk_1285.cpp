	if (status != Z_STREAM_END || stream.total_out != obj->size)
		die(_("serious inflate inconsistency"));

	git_inflate_end(&stream);
	free(inbuf);
	if (consume) {
		free(data);
		data = NULL;
	}
	return data;
}

static void *get_data_from_pack(struct object_entry *obj)
{
