struct msg_list {
	struct msg_list_item *head, *tail;
};

static struct msg_list msg_queue;

static void got_flist_entry_status(enum festatus status, const char *buf)
{
	int ndx = IVAL(buf, 0);
	struct file_list *flist = flist_for_ndx(ndx, "got_flist_entry_status");

	if (remove_source_files) {
