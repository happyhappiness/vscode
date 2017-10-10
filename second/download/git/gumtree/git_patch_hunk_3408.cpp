 	struct strbuf buf = STRBUF_INIT;
 	struct strbuf *pbuf = &buf;
 
 	args_gpg[0] = gpg_program;
 	fd = git_mkstemp(path, PATH_MAX, ".git_vtag_tmpXXXXXX");
 	if (fd < 0)
-		return error(_("could not create temporary file '%s': %s"),
-			     path, strerror(errno));
+		return error_errno(_("could not create temporary file '%s'"), path);
 	if (write_in_full(fd, signature, signature_size) < 0)
-		return error(_("failed writing detached signature to '%s': %s"),
-			     path, strerror(errno));
+		return error_errno(_("failed writing detached signature to '%s'"), path);
 	close(fd);
 
 	gpg.argv = args_gpg;
 	gpg.in = -1;
 	gpg.out = -1;
 	if (gpg_output)
