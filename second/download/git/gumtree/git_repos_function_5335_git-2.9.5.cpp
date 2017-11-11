static void clone_local(const char *src_repo, const char *dest_repo)
{
	if (option_shared) {
		struct strbuf alt = STRBUF_INIT;
		strbuf_addf(&alt, "%s/objects", src_repo);
		add_to_alternates_file(alt.buf);
		strbuf_release(&alt);
	} else {
		struct strbuf src = STRBUF_INIT;
		struct strbuf dest = STRBUF_INIT;
		get_common_dir(&src, src_repo);
		get_common_dir(&dest, dest_repo);
		strbuf_addstr(&src, "/objects");
		strbuf_addstr(&dest, "/objects");
		copy_or_link_directory(&src, &dest, src_repo, src.len);
		strbuf_release(&src);
		strbuf_release(&dest);
	}

	if (0 <= option_verbosity)
		fprintf(stderr, _("done.\n"));
}