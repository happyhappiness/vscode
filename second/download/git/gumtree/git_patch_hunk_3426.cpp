 		error("%s", err.buf);
 
 	string_list_clear(&skip, 0);
 	strbuf_release(&err);
 	return ret;
 }
+
+int head_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
+{
+	struct object_id oid;
+	int flag;
+
+	if (submodule) {
+		if (resolve_gitlink_ref(submodule, "HEAD", oid.hash) == 0)
+			return fn("HEAD", &oid, 0, cb_data);
+
+		return 0;
+	}
+
+	if (!read_ref_full("HEAD", RESOLVE_REF_READING, oid.hash, &flag))
+		return fn("HEAD", &oid, flag, cb_data);
+
+	return 0;
+}
+
+int head_ref(each_ref_fn fn, void *cb_data)
+{
+	return head_ref_submodule(NULL, fn, cb_data);
+}
+
+int for_each_ref(each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(NULL, "", fn, 0, 0, cb_data);
+}
+
+int for_each_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(submodule, "", fn, 0, 0, cb_data);
+}
+
+int for_each_ref_in(const char *prefix, each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(NULL, prefix, fn, strlen(prefix), 0, cb_data);
+}
+
+int for_each_fullref_in(const char *prefix, each_ref_fn fn, void *cb_data, unsigned int broken)
+{
+	unsigned int flag = 0;
+
+	if (broken)
+		flag = DO_FOR_EACH_INCLUDE_BROKEN;
+	return do_for_each_ref(NULL, prefix, fn, 0, flag, cb_data);
+}
+
+int for_each_ref_in_submodule(const char *submodule, const char *prefix,
+		each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(submodule, prefix, fn, strlen(prefix), 0, cb_data);
+}
+
+int for_each_replace_ref(each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(NULL, git_replace_ref_base, fn,
+			       strlen(git_replace_ref_base), 0, cb_data);
+}
+
+int for_each_namespaced_ref(each_ref_fn fn, void *cb_data)
+{
+	struct strbuf buf = STRBUF_INIT;
+	int ret;
+	strbuf_addf(&buf, "%srefs/", get_git_namespace());
+	ret = do_for_each_ref(NULL, buf.buf, fn, 0, 0, cb_data);
+	strbuf_release(&buf);
+	return ret;
+}
+
+int for_each_rawref(each_ref_fn fn, void *cb_data)
+{
+	return do_for_each_ref(NULL, "", fn, 0,
+			       DO_FOR_EACH_INCLUDE_BROKEN, cb_data);
+}
+
+/* This function needs to return a meaningful errno on failure */
+const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
+			       unsigned char *sha1, int *flags)
+{
+	static struct strbuf sb_refname = STRBUF_INIT;
+	int unused_flags;
+	int symref_count;
+
+	if (!flags)
+		flags = &unused_flags;
+
+	*flags = 0;
+
+	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
+		if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
+		    !refname_is_safe(refname)) {
+			errno = EINVAL;
+			return NULL;
+		}
+
+		/*
+		 * dwim_ref() uses REF_ISBROKEN to distinguish between
+		 * missing refs and refs that were present but invalid,
+		 * to complain about the latter to stderr.
+		 *
+		 * We don't know whether the ref exists, so don't set
+		 * REF_ISBROKEN yet.
+		 */
+		*flags |= REF_BAD_NAME;
+	}
+
+	for (symref_count = 0; symref_count < SYMREF_MAXDEPTH; symref_count++) {
+		unsigned int read_flags = 0;
+
+		if (read_raw_ref(refname, sha1, &sb_refname, &read_flags)) {
+			*flags |= read_flags;
+			if (errno != ENOENT || (resolve_flags & RESOLVE_REF_READING))
+				return NULL;
+			hashclr(sha1);
+			if (*flags & REF_BAD_NAME)
+				*flags |= REF_ISBROKEN;
+			return refname;
+		}
+
+		*flags |= read_flags;
+
+		if (!(read_flags & REF_ISSYMREF)) {
+			if (*flags & REF_BAD_NAME) {
+				hashclr(sha1);
+				*flags |= REF_ISBROKEN;
+			}
+			return refname;
+		}
+
+		refname = sb_refname.buf;
+		if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
+			hashclr(sha1);
+			return refname;
+		}
+		if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
+			if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
+			    !refname_is_safe(refname)) {
+				errno = EINVAL;
+				return NULL;
+			}
+
+			*flags |= REF_ISBROKEN | REF_BAD_NAME;
+		}
+	}
+
+	errno = ELOOP;
+	return NULL;
+}
