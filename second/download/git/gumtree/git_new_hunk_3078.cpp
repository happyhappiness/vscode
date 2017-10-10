	git_path_buf(&path, "%s", auml_nfc);
	output_fd = open(path.buf, O_CREAT|O_EXCL|O_RDWR, 0600);
	if (output_fd >= 0) {
		close(output_fd);
		git_path_buf(&path, "%s", auml_nfd);
		precomposed_unicode = access(path.buf, R_OK) ? 0 : 1;
		git_config_set("core.precomposeunicode",
			       precomposed_unicode ? "true" : "false");
		git_path_buf(&path, "%s", auml_nfc);
		if (unlink(path.buf))
			die_errno(_("failed to unlink '%s'"), path.buf);
	}
	strbuf_release(&path);
}
