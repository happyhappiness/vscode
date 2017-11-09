static int handle_line(char *line, struct merge_parents *merge_parents)
{
	int i, len = strlen(line);
	struct origin_data *origin_data;
	char *src;
	const char *origin;
	struct src_data *src_data;
	struct string_list_item *item;
	int pulling_head = 0;
	struct object_id oid;

	if (len < GIT_SHA1_HEXSZ + 3 || line[GIT_SHA1_HEXSZ] != '\t')
		return 1;

	if (starts_with(line + GIT_SHA1_HEXSZ + 1, "not-for-merge"))
		return 0;

	if (line[GIT_SHA1_HEXSZ + 1] != '\t')
		return 2;

	i = get_oid_hex(line, &oid);
	if (i)
		return 3;

	if (!find_merge_parent(merge_parents, &oid, NULL))
		return 0; /* subsumed by other parents */

	origin_data = xcalloc(1, sizeof(struct origin_data));
	oidcpy(&origin_data->oid, &oid);

	if (line[len - 1] == '\n')
		line[len - 1] = 0;
	line += GIT_SHA1_HEXSZ + 2;

	/*
	 * At this point, line points at the beginning of comment e.g.
	 * "branch 'frotz' of git://that/repository.git".
	 * Find the repository name and point it with src.
	 */
	src = strstr(line, " of ");
	if (src) {
		*src = 0;
		src += 4;
		pulling_head = 0;
	} else {
		src = line;
		pulling_head = 1;
	}

	item = unsorted_string_list_lookup(&srcs, src);
	if (!item) {
		item = string_list_append(&srcs, src);
		item->util = xcalloc(1, sizeof(struct src_data));
		init_src_data(item->util);
	}
	src_data = item->util;

	if (pulling_head) {
		origin = src;
		src_data->head_status |= 1;
	} else if (starts_with(line, "branch ")) {
		origin_data->is_local_branch = 1;
		origin = line + 7;
		string_list_append(&src_data->branch, origin);
		src_data->head_status |= 2;
	} else if (starts_with(line, "tag ")) {
		origin = line;
		string_list_append(&src_data->tag, origin + 4);
		src_data->head_status |= 2;
	} else if (skip_prefix(line, "remote-tracking branch ", &origin)) {
		string_list_append(&src_data->r_branch, origin);
		src_data->head_status |= 2;
	} else {
		origin = src;
		string_list_append(&src_data->generic, line);
		src_data->head_status |= 2;
	}

	if (!strcmp(".", src) || !strcmp(src, origin)) {
		int len = strlen(origin);
		if (origin[0] == '\'' && origin[len - 1] == '\'')
			origin = xmemdupz(origin + 1, len - 2);
	} else
		origin = xstrfmt("%s of %s", origin, src);
	if (strcmp(".", src))
		origin_data->is_local_branch = 0;
	string_list_append(&origins, origin)->util = origin_data;
	return 0;
}