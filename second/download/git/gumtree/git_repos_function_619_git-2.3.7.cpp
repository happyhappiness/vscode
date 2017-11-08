void parse_commit_or_die(struct commit *item)
{
	if (parse_commit(item))
		die("unable to parse commit %s",
		    item ? sha1_to_hex(item->object.sha1) : "(null)");
}