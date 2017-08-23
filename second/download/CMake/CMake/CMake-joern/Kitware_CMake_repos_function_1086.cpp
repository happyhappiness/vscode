static int
error_nomem(struct archive_match *a)
{
	archive_set_error(&(a->archive), ENOMEM, "No memory");
	a->archive.state = ARCHIVE_STATE_FATAL;
	return (ARCHIVE_FATAL);
}