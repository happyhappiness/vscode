 
 	if (args->verbose)
 		fprintf(stderr, "%.*s\n", (int)path.len, path.buf);
 	return write_entry(args, sha1, path.buf, path.len, mode);
 }
 
+static int write_archive_entry_buf(const unsigned char *sha1, struct strbuf *base,
+		const char *filename, unsigned mode, int stage,
+		void *context)
+{
+	return write_archive_entry(sha1, base->buf, base->len,
+				     filename, mode, stage, context);
+}
+
 static void queue_directory(const unsigned char *sha1,
-		const char *base, int baselen, const char *filename,
+		struct strbuf *base, const char *filename,
 		unsigned mode, int stage, struct archiver_context *c)
 {
 	struct directory *d;
-	d = xmallocz(sizeof(*d) + baselen + 1 + strlen(filename));
+	d = xmallocz(sizeof(*d) + base->len + 1 + strlen(filename));
 	d->up	   = c->bottom;
-	d->baselen = baselen;
+	d->baselen = base->len;
 	d->mode	   = mode;
 	d->stage   = stage;
 	c->bottom  = d;
-	d->len = sprintf(d->path, "%.*s%s/", baselen, base, filename);
+	d->len = sprintf(d->path, "%.*s%s/", (int)base->len, base->buf, filename);
 	hashcpy(d->sha1, sha1);
 }
 
 static int write_directory(struct archiver_context *c)
 {
 	struct directory *d = c->bottom;
