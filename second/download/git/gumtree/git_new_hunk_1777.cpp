		unsigned char sha1[20];
		if (buf.len > 0 && buf.buf[0] == '-') {
			write_or_die(bundle_fd, buf.buf, buf.len);
			if (!get_sha1_hex(buf.buf + 1, sha1)) {
				struct object *object = parse_object_or_die(sha1, buf.buf);
				object->flags |= UNINTERESTING;
				add_pending_object(revs, object, buf.buf);
			}
		} else if (!get_sha1_hex(buf.buf, sha1)) {
			struct object *object = parse_object_or_die(sha1, buf.buf);
			object->flags |= SHOWN;
		}
	}
	strbuf_release(&buf);
	fclose(rls_fout);
	if (finish_command(&rls))
		return error(_("rev-list died"));
	return 0;
}

/*
 * Write out bundle refs based on the tips already
 * parsed into revs.pending. As a side effect, may
 * manipulate revs.pending to include additional
 * necessary objects (like tags).
 *
 * Returns the number of refs written, or negative
 * on error.
 */
static int write_bundle_refs(int bundle_fd, struct rev_info *revs)
{
	int i;
	int ref_count = 0;

	for (i = 0; i < revs->pending.nr; i++) {
		struct object_array_entry *e = revs->pending.objects + i;
		unsigned char sha1[20];
		char *ref;
		const char *display_ref;
		int flag;

		if (e->item->flags & UNINTERESTING)
			continue;
		if (dwim_ref(e->name, strlen(e->name), sha1, &ref) != 1)
			continue;
		if (read_ref_full(e->name, RESOLVE_REF_READING, sha1, &flag))
			flag = 0;
		display_ref = (flag & REF_ISSYMREF) ? e->name : ref;

		if (e->item->type == OBJ_TAG &&
				!is_tag_in_date_range(e->item, revs)) {
			e->item->flags |= UNINTERESTING;
			continue;
		}

		/*
		 * Make sure the refs we wrote out is correct; --max-count and
