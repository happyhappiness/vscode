static int compute_and_write_prerequisites(int bundle_fd,
					   struct rev_info *revs,
					   int argc, const char **argv)
{
	struct child_process rls = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	FILE *rls_fout;
	int i;

	argv_array_pushl(&rls.args,
			 "rev-list", "--boundary", "--pretty=oneline",
			 NULL);
	for (i = 1; i < argc; i++)
		argv_array_push(&rls.args, argv[i]);
	rls.out = -1;
	rls.git_cmd = 1;
	if (start_command(&rls))
		return -1;
	rls_fout = xfdopen(rls.out, "r");
	while (strbuf_getwholeline(&buf, rls_fout, '\n') != EOF) {
		struct object_id oid;
		if (buf.len > 0 && buf.buf[0] == '-') {
			write_or_die(bundle_fd, buf.buf, buf.len);
			if (!get_oid_hex(buf.buf + 1, &oid)) {
				struct object *object = parse_object_or_die(&oid,
									    buf.buf);
				object->flags |= UNINTERESTING;
				add_pending_object(revs, object, buf.buf);
			}
		} else if (!get_oid_hex(buf.buf, &oid)) {
			struct object *object = parse_object_or_die(&oid,
								    buf.buf);
			object->flags |= SHOWN;
		}
	}
	strbuf_release(&buf);
	fclose(rls_fout);
	if (finish_command(&rls))
		return error(_("rev-list died"));
	return 0;
}