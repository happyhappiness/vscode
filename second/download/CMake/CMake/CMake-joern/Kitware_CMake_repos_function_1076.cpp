static int
uudecode_bidder_init(struct archive_read_filter *self)
{
	struct uudecode   *uudecode;
	void *out_buff;
	void *in_buff;

	self->code = ARCHIVE_FILTER_UU;
	self->name = "uu";
	self->read = uudecode_filter_read;
	self->skip = NULL; /* not supported */
	self->close = uudecode_filter_close;

	uudecode = (struct uudecode *)calloc(sizeof(*uudecode), 1);
	out_buff = malloc(OUT_BUFF_SIZE);
	in_buff = malloc(IN_BUFF_SIZE);
	if (uudecode == NULL || out_buff == NULL || in_buff == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for uudecode");
		free(uudecode);
		free(out_buff);
		free(in_buff);
		return (ARCHIVE_FATAL);
	}

	self->data = uudecode;
	uudecode->in_buff = in_buff;
	uudecode->in_cnt = 0;
	uudecode->in_allocated = IN_BUFF_SIZE;
	uudecode->out_buff = out_buff;
	uudecode->state = ST_FIND_HEAD;

	return (ARCHIVE_OK);
}