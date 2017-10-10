 	if (type < 0)
 		die("%s is not a valid object", sha1_to_hex(sha1));
 	if (type != expect)
 		die("%s is not a valid '%s' object", sha1_to_hex(sha1),
 		    typename(expect));
 }
+
+static int for_each_file_in_obj_subdir(int subdir_nr,
+				       struct strbuf *path,
+				       each_loose_object_fn obj_cb,
+				       each_loose_cruft_fn cruft_cb,
+				       each_loose_subdir_fn subdir_cb,
+				       void *data)
+{
+	size_t baselen = path->len;
+	DIR *dir = opendir(path->buf);
+	struct dirent *de;
+	int r = 0;
+
+	if (!dir) {
+		if (errno == ENOENT)
+			return 0;
+		return error("unable to open %s: %s", path->buf, strerror(errno));
+	}
+
+	while ((de = readdir(dir))) {
+		if (is_dot_or_dotdot(de->d_name))
+			continue;
+
+		strbuf_setlen(path, baselen);
+		strbuf_addf(path, "/%s", de->d_name);
+
+		if (strlen(de->d_name) == 38)  {
+			char hex[41];
+			unsigned char sha1[20];
+
+			snprintf(hex, sizeof(hex), "%02x%s",
+				 subdir_nr, de->d_name);
+			if (!get_sha1_hex(hex, sha1)) {
+				if (obj_cb) {
+					r = obj_cb(sha1, path->buf, data);
+					if (r)
+						break;
+				}
+				continue;
+			}
+		}
+
+		if (cruft_cb) {
+			r = cruft_cb(de->d_name, path->buf, data);
+			if (r)
+				break;
+		}
+	}
+	strbuf_setlen(path, baselen);
+
+	if (!r && subdir_cb)
+		r = subdir_cb(subdir_nr, path->buf, data);
+
+	closedir(dir);
+	return r;
+}
+
+int for_each_loose_file_in_objdir(const char *path,
+			    each_loose_object_fn obj_cb,
+			    each_loose_cruft_fn cruft_cb,
+			    each_loose_subdir_fn subdir_cb,
+			    void *data)
+{
+	struct strbuf buf = STRBUF_INIT;
+	size_t baselen;
+	int r = 0;
+	int i;
+
+	strbuf_addstr(&buf, path);
+	strbuf_addch(&buf, '/');
+	baselen = buf.len;
+
+	for (i = 0; i < 256; i++) {
+		strbuf_addf(&buf, "%02x", i);
+		r = for_each_file_in_obj_subdir(i, &buf, obj_cb, cruft_cb,
+						subdir_cb, data);
+		strbuf_setlen(&buf, baselen);
+		if (r)
+			break;
+	}
+
+	strbuf_release(&buf);
+	return r;
+}
+
+struct loose_alt_odb_data {
+	each_loose_object_fn *cb;
+	void *data;
+};
+
+static int loose_from_alt_odb(struct alternate_object_database *alt,
+			      void *vdata)
+{
+	struct loose_alt_odb_data *data = vdata;
+	return for_each_loose_file_in_objdir(alt->base,
+					     data->cb, NULL, NULL,
+					     data->data);
+}
+
+int for_each_loose_object(each_loose_object_fn cb, void *data)
+{
+	struct loose_alt_odb_data alt;
+	int r;
+
+	r = for_each_loose_file_in_objdir(get_object_directory(),
+					  cb, NULL, NULL, data);
+	if (r)
+		return r;
+
+	alt.cb = cb;
+	alt.data = data;
+	return foreach_alt_odb(loose_from_alt_odb, &alt);
+}
+
+static int for_each_object_in_pack(struct packed_git *p, each_packed_object_fn cb, void *data)
+{
+	uint32_t i;
+	int r = 0;
+
+	for (i = 0; i < p->num_objects; i++) {
+		const unsigned char *sha1 = nth_packed_object_sha1(p, i);
+
+		if (!sha1)
+			return error("unable to get sha1 of object %u in %s",
+				     i, p->pack_name);
+
+		r = cb(sha1, p, i, data);
+		if (r)
+			break;
+	}
+	return r;
+}
+
+int for_each_packed_object(each_packed_object_fn cb, void *data)
+{
+	struct packed_git *p;
+	int r = 0;
+
+	prepare_packed_git();
+	for (p = packed_git; p; p = p->next) {
+		r = for_each_object_in_pack(p, cb, data);
+		if (r)
+			break;
+	}
+	return r;
+}
