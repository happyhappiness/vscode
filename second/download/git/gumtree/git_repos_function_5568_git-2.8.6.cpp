static void prepare_merge_message(struct strbuf *merge_names, struct strbuf *merge_msg)
{
	struct fmt_merge_msg_opts opts;

	memset(&opts, 0, sizeof(opts));
	opts.add_title = !have_message;
	opts.shortlog_len = shortlog_len;
	opts.credit_people = (0 < option_edit);

	fmt_merge_msg(merge_names, merge_msg, &opts);
	if (merge_msg->len)
		strbuf_setlen(merge_msg, merge_msg->len - 1);
}