static void get_commit_info(struct commit *commit,
			    struct commit_info *ret,
			    int detailed)
{
	int len;
	const char *subject, *encoding;
	const char *message;

	commit_info_init(ret);

	encoding = get_log_output_encoding();
	message = logmsg_reencode(commit, NULL, encoding);
	get_ac_line(message, "\nauthor ",
		    &ret->author, &ret->author_mail,
		    &ret->author_time, &ret->author_tz);

	if (!detailed) {
		unuse_commit_buffer(commit, message);
		return;
	}

	get_ac_line(message, "\ncommitter ",
		    &ret->committer, &ret->committer_mail,
		    &ret->committer_time, &ret->committer_tz);

	len = find_commit_subject(message, &subject);
	if (len)
		strbuf_add(&ret->summary, subject, len);
	else
		strbuf_addf(&ret->summary, "(%s)", sha1_to_hex(commit->object.sha1));

	unuse_commit_buffer(commit, message);
}