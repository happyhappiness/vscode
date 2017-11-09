static int get_reachable_list(struct object_array *src,
			      struct object_array *reachable)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int i;
	struct object *o;
	char namebuf[42]; /* ^ + SHA-1 + LF */

	if (do_reachable_revlist(&cmd, src, reachable) < 0)
		return -1;

	while ((i = read_in_full(cmd.out, namebuf, 41)) == 41) {
		struct object_id sha1;

		if (namebuf[40] != '\n' || get_oid_hex(namebuf, &sha1))
			break;

		o = lookup_object(sha1.hash);
		if (o && o->type == OBJ_COMMIT) {
			o->flags &= ~TMP_MARK;
		}
	}
	for (i = get_max_object_index(); 0 < i; i--) {
		o = get_indexed_object(i - 1);
		if (o && o->type == OBJ_COMMIT &&
		    (o->flags & TMP_MARK)) {
			add_object_array(o, NULL, reachable);
				o->flags &= ~TMP_MARK;
		}
	}
	close(cmd.out);

	if (finish_command(&cmd))
		return -1;

	return 0;
}