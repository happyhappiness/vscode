
struct commit_graft *read_graft_line(char *buf, int len)
{
	/* The format is just "Commit Parent1 Parent2 ...\n" */
	int i;
	struct commit_graft *graft = NULL;

	while (len && isspace(buf[len-1]))
		buf[--len] = '\0';
	if (buf[0] == '#' || buf[0] == '\0')
		return NULL;
	if ((len + 1) % 41)
		goto bad_graft_data;
	i = (len + 1) / 41 - 1;
	graft = xmalloc(sizeof(*graft) + 20 * i);
	graft->nr_parent = i;
	if (get_sha1_hex(buf, graft->sha1))
		goto bad_graft_data;
	for (i = 40; i < len; i += 41) {
		if (buf[i] != ' ')
			goto bad_graft_data;
		if (get_sha1_hex(buf + i + 1, graft->parent[i/41]))
			goto bad_graft_data;
	}
	return graft;

bad_graft_data:
	error("bad graft data: %s", buf);
