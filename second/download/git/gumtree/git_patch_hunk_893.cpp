 		default:
 			return error(_("could not create leading directories "
 				       "of '%s'"), path);
 	}
 }
 
+/*
+ * Unconditional writing of a plain regular file is what
+ * "git difftool --dir-diff" wants to do for symlinks.  We are preparing two
+ * temporary directories to be fed to a Git-unaware tool that knows how to
+ * show a diff of two directories (e.g. "diff -r A B").
+ *
+ * Because the tool is Git-unaware, if a symbolic link appears in either of
+ * these temporary directories, it will try to dereference and show the
+ * difference of the target of the symbolic link, which is not what we want,
+ * as the goal of the dir-diff mode is to produce an output that is logically
+ * equivalent to what "git diff" produces.
+ *
+ * Most importantly, we want to get textual comparison of the result of the
+ * readlink(2).  get_symlink() provides that---it returns the contents of
+ * the symlink that gets written to a regular file to force the external tool
+ * to compare the readlink(2) result as text, even on a filesystem that is
+ * capable of doing a symbolic link.
+ */
+static char *get_symlink(const struct object_id *oid, const char *path)
+{
+	char *data;
+	if (is_null_oid(oid)) {
+		/* The symlink is unknown to Git so read from the filesystem */
+		struct strbuf link = STRBUF_INIT;
+		if (has_symlinks) {
+			if (strbuf_readlink(&link, path, strlen(path)))
+				die(_("could not read symlink %s"), path);
+		} else if (strbuf_read_file(&link, path, 128))
+			die(_("could not read symlink file %s"), path);
+
+		data = strbuf_detach(&link, NULL);
+	} else {
+		enum object_type type;
+		unsigned long size;
+		data = read_sha1_file(oid->hash, &type, &size);
+		if (!data)
+			die(_("could not read object %s for symlink %s"),
+				oid_to_hex(oid), path);
+	}
+
+	return data;
+}
+
+static int checkout_path(unsigned mode, struct object_id *oid,
+			 const char *path, const struct checkout *state)
+{
+	struct cache_entry *ce;
+	int ret;
+
+	ce = make_cache_entry(mode, oid->hash, path, 0, 0);
+	ret = checkout_entry(ce, state, NULL);
+
+	free(ce);
+	return ret;
+}
+
 static int run_dir_diff(const char *extcmd, int symlinks, const char *prefix,
 			int argc, const char **argv)
 {
 	char tmpdir[PATH_MAX];
 	struct strbuf info = STRBUF_INIT, lpath = STRBUF_INIT;
 	struct strbuf rpath = STRBUF_INIT, buf = STRBUF_INIT;
 	struct strbuf ldir = STRBUF_INIT, rdir = STRBUF_INIT;
 	struct strbuf wtdir = STRBUF_INIT;
+	char *lbase_dir, *rbase_dir;
 	size_t ldir_len, rdir_len, wtdir_len;
-	struct cache_entry *ce = xcalloc(1, sizeof(ce) + PATH_MAX + 1);
 	const char *workdir, *tmp;
 	int ret = 0, i;
 	FILE *fp;
 	struct hashmap working_tree_dups, submodules, symlinks2;
 	struct hashmap_iter iter;
 	struct pair_entry *entry;
-	enum object_type type;
-	unsigned long size;
 	struct index_state wtindex;
 	struct checkout lstate, rstate;
 	int rc, flags = RUN_GIT_CMD, err = 0;
 	struct child_process child = CHILD_PROCESS_INIT;
 	const char *helper_argv[] = { "difftool--helper", NULL, NULL, NULL };
 	struct hashmap wt_modified, tmp_modified;
