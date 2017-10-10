 
 void show_decorations(struct rev_info *opt, struct commit *commit)
 {
 	struct strbuf sb = STRBUF_INIT;
 
 	if (opt->show_source && commit->util)
-		printf("\t%s", (char *) commit->util);
+		fprintf(opt->diffopt.file, "\t%s", (char *) commit->util);
 	if (!opt->show_decorations)
 		return;
 	format_decorations(&sb, commit, opt->diffopt.use_color);
-	fputs(sb.buf, stdout);
+	fputs(sb.buf, opt->diffopt.file);
 	strbuf_release(&sb);
 }
 
 static unsigned int digits_in_number(unsigned int number)
 {
 	unsigned int i = 10, result = 1;
