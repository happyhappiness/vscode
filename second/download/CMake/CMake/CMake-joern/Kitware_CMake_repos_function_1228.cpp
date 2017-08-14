static int
rpm_bidder_init(struct archive_read_filter *self)
{
	struct rpm   *rpm;

	self->code = ARCHIVE_FILTER_RPM;
	self->name = "rpm";
	self->read = rpm_filter_read;
	self->skip = NULL; /* not supported */
	self->close = rpm_filter_close;

	rpm = (struct rpm *)calloc(sizeof(*rpm), 1);
	if (rpm == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for rpm");
		return (ARCHIVE_FATAL);
	}

	self->data = rpm;
	rpm->state = ST_LEAD;

	return (ARCHIVE_OK);
}