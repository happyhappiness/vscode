 }
 
 static int parse_reuse_arg(const struct option *opt, const char *arg, int unset)
 {
 	struct note_data *d = opt->value;
 	char *buf;
-	unsigned char object[20];
+	struct object_id object;
 	enum object_type type;
 	unsigned long len;
 
 	if (d->buf.len)
 		strbuf_addch(&d->buf, '\n');
 
-	if (get_sha1(arg, object))
+	if (get_oid(arg, &object))
 		die(_("failed to resolve '%s' as a valid ref."), arg);
-	if (!(buf = read_sha1_file(object, &type, &len))) {
+	if (!(buf = read_sha1_file(object.hash, &type, &len))) {
 		free(buf);
 		die(_("failed to read object '%s'."), arg);
 	}
 	if (type != OBJ_BLOB) {
 		free(buf);
 		die(_("cannot read note data from non-blob object '%s'."), arg);
