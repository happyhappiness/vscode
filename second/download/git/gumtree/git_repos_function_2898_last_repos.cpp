static void show_one_mergetag(struct commit *commit,
			      struct commit_extra_header *extra,
			      void *data)
{
	struct rev_info *opt = (struct rev_info *)data;
	struct object_id oid;
	struct tag *tag;
	struct strbuf verify_message;
	int status, nth;
	size_t payload_size, gpg_message_offset;

	hash_sha1_file(extra->value, extra->len, typename(OBJ_TAG), oid.hash);
	tag = lookup_tag(&oid);
	if (!tag)
		return; /* error message already given */

	strbuf_init(&verify_message, 256);
	if (parse_tag_buffer(tag, extra->value, extra->len))
		strbuf_addstr(&verify_message, "malformed mergetag\n");
	else if (is_common_merge(commit) &&
		 !oidcmp(&tag->tagged->oid,
			  &commit->parents->next->item->object.oid))
		strbuf_addf(&verify_message,
			    "merged tag '%s'\n", tag->tag);
	else if ((nth = which_parent(&tag->tagged->oid, commit)) < 0)
		strbuf_addf(&verify_message, "tag %s names a non-parent %s\n",
				    tag->tag, tag->tagged->oid.hash);
	else
		strbuf_addf(&verify_message,
			    "parent #%d, tagged '%s'\n", nth + 1, tag->tag);
	gpg_message_offset = verify_message.len;

	payload_size = parse_signature(extra->value, extra->len);
	status = -1;
	if (extra->len > payload_size) {
		/* could have a good signature */
		if (!verify_signed_buffer(extra->value, payload_size,
					  extra->value + payload_size,
					  extra->len - payload_size,
					  &verify_message, NULL))
			status = 0; /* good */
		else if (verify_message.len <= gpg_message_offset)
			strbuf_addstr(&verify_message, "No signature\n");
		/* otherwise we couldn't verify, which is shown as bad */
	}

	show_sig_lines(opt, status, verify_message.buf);
	strbuf_release(&verify_message);
}