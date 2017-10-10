 #include "commit.h"
 #include "tree.h"
 #include "blob.h"
 
 const char *tag_type = "tag";
 
+static int run_gpg_verify(const char *buf, unsigned long size, unsigned flags)
+{
+	struct signature_check sigc;
+	size_t payload_size;
+	int ret;
+
+	memset(&sigc, 0, sizeof(sigc));
+
+	payload_size = parse_signature(buf, size);
+
+	if (size == payload_size) {
+		if (flags & GPG_VERIFY_VERBOSE)
+			write_in_full(1, buf, payload_size);
+		return error("no signature found");
+	}
+
+	ret = check_signature(buf, payload_size, buf + payload_size,
+				size - payload_size, &sigc);
+	print_signature_buffer(&sigc, flags);
+
+	signature_check_clear(&sigc);
+	return ret;
+}
+
+int gpg_verify_tag(const unsigned char *sha1, const char *name_to_report,
+		unsigned flags)
+{
+	enum object_type type;
+	char *buf;
+	unsigned long size;
+	int ret;
+
+	type = sha1_object_info(sha1, NULL);
+	if (type != OBJ_TAG)
+		return error("%s: cannot verify a non-tag object of type %s.",
+				name_to_report ?
+				name_to_report :
+				find_unique_abbrev(sha1, DEFAULT_ABBREV),
+				typename(type));
+
+	buf = read_sha1_file(sha1, &type, &size);
+	if (!buf)
+		return error("%s: unable to read file.",
+				name_to_report ?
+				name_to_report :
+				find_unique_abbrev(sha1, DEFAULT_ABBREV));
+
+	ret = run_gpg_verify(buf, size, flags);
+
+	free(buf);
+	return ret;
+}
+
 struct object *deref_tag(struct object *o, const char *warn, int warnlen)
 {
 	while (o && o->type == OBJ_TAG)
 		if (((struct tag *)o)->tagged)
 			o = parse_object(((struct tag *)o)->tagged->oid.hash);
 		else
