static int write_one_shallow(const struct commit_graft *graft, void *cb_data)
{
	struct write_shallow_data *data = cb_data;
	const char *hex = oid_to_hex(&graft->oid);
	if (graft->nr_parent != -1)
		return 0;
	if (data->flags & SEEN_ONLY) {
		struct commit *c = lookup_commit(&graft->oid);
		if (!c || !(c->object.flags & SEEN)) {
			if (data->flags & VERBOSE)
				printf("Removing %s from .git/shallow\n",
				       oid_to_hex(&c->object.oid));
			return 0;
		}
	}
	data->count++;
	if (data->use_pack_protocol)
		packet_buf_write(data->out, "shallow %s", hex);
	else {
		strbuf_addstr(data->out, hex);
		strbuf_addch(data->out, '\n');
	}
	return 0;
}