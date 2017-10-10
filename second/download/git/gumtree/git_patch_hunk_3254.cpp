 	while (*first) {
 		struct trailer_item *item = remove_first(first);
 		free_trailer_item(item);
 	}
 }
 
-void process_trailers(const char *file, int trim_empty, struct string_list *trailers)
+static struct tempfile trailers_tempfile;
+
+static FILE *create_in_place_tempfile(const char *file)
+{
+	struct stat st;
+	struct strbuf template = STRBUF_INIT;
+	const char *tail;
+	FILE *outfile;
+
+	if (stat(file, &st))
+		die_errno(_("could not stat %s"), file);
+	if (!S_ISREG(st.st_mode))
+		die(_("file %s is not a regular file"), file);
+	if (!(st.st_mode & S_IWUSR))
+		die(_("file %s is not writable by user"), file);
+
+	/* Create temporary file in the same directory as the original */
+	tail = strrchr(file, '/');
+	if (tail != NULL)
+		strbuf_add(&template, file, tail - file + 1);
+	strbuf_addstr(&template, "git-interpret-trailers-XXXXXX");
+
+	xmks_tempfile_m(&trailers_tempfile, template.buf, st.st_mode);
+	strbuf_release(&template);
+	outfile = fdopen_tempfile(&trailers_tempfile, "w");
+	if (!outfile)
+		die_errno(_("could not open temporary file"));
+
+	return outfile;
+}
+
+void process_trailers(const char *file, int in_place, int trim_empty, struct string_list *trailers)
 {
 	struct trailer_item *in_tok_first = NULL;
 	struct trailer_item *in_tok_last = NULL;
 	struct trailer_item *arg_tok_first;
 	struct strbuf **lines;
 	int trailer_end;
+	FILE *outfile = stdout;
 
 	/* Default config must be setup first */
 	git_config(git_trailer_default_config, NULL);
 	git_config(git_trailer_config, NULL);
 
 	lines = read_input_file(file);
 
+	if (in_place)
+		outfile = create_in_place_tempfile(file);
+
 	/* Print the lines before the trailers */
-	trailer_end = process_input_file(lines, &in_tok_first, &in_tok_last);
+	trailer_end = process_input_file(outfile, lines, &in_tok_first, &in_tok_last);
 
 	arg_tok_first = process_command_line_args(trailers);
 
 	process_trailers_lists(&in_tok_first, &in_tok_last, &arg_tok_first);
 
-	print_all(in_tok_first, trim_empty);
+	print_all(outfile, in_tok_first, trim_empty);
 
 	free_all(&in_tok_first);
 
 	/* Print the lines after the trailers as is */
-	print_lines(lines, trailer_end, INT_MAX);
+	print_lines(outfile, lines, trailer_end, INT_MAX);
+
+	if (in_place)
+		if (rename_tempfile(&trailers_tempfile, file))
+			die_errno(_("could not rename temporary file to %s"), file);
 
 	strbuf_list_free(lines);
 }
