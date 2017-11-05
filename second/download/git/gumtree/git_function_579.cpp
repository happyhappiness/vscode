static int rollback_is_safe(void)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id expected_head, actual_head;

	if (strbuf_read_file(&sb, git_path_abort_safety_file(), 0) >= 0) {
		strbuf_trim(&sb);
		if (get_oid_hex(sb.buf, &expected_head)) {
			strbuf_release(&sb);
			die(_("could not parse %s"), git_path_abort_safety_file());
		}
		strbuf_release(&sb);
	}
	else if (errno == ENOENT)
		oidclr(&expected_head);
	else
		die_errno(_("could not read '%s'"), git_path_abort_safety_file());

	if (get_oid("HEAD", &actual_head))
		oidclr(&actual_head);

	return !oidcmp(&actual_head, &expected_head);
}