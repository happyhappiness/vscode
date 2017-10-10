 	unsigned char junk[20];
 
 	if (!(flags & REF_ISSYMREF))
 		return 0;
 
 	resolves_to = resolve_ref_unsafe(refname, junk, 0, NULL);
-	if (!resolves_to || strcmp(resolves_to, d->refname))
+	if (!resolves_to
+	    || (d->refname
+		? strcmp(resolves_to, d->refname)
+		: !string_list_has_string(d->refnames, resolves_to))) {
 		return 0;
+	}
 
 	fprintf(d->fp, d->msg_fmt, refname);
 	fputc('\n', d->fp);
 	return 0;
 }
 
 void warn_dangling_symref(FILE *fp, const char *msg_fmt, const char *refname)
 {
 	struct warn_if_dangling_data data;
 
 	data.fp = fp;
 	data.refname = refname;
+	data.refnames = NULL;
+	data.msg_fmt = msg_fmt;
+	for_each_rawref(warn_if_dangling_symref, &data);
+}
+
+void warn_dangling_symrefs(FILE *fp, const char *msg_fmt, const struct string_list *refnames)
+{
+	struct warn_if_dangling_data data;
+
+	data.fp = fp;
+	data.refname = NULL;
+	data.refnames = refnames;
 	data.msg_fmt = msg_fmt;
 	for_each_rawref(warn_if_dangling_symref, &data);
 }
 
 /*
  * Call fn for each reference in the specified ref_cache, omitting
