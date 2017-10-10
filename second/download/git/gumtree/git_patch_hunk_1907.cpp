 #include "cache.h"
 #include "refs.h"
 #include "object.h"
 #include "commit.h"
 #include "tag.h"
 
-/* refs */
-static FILE *info_ref_fp;
+/*
+ * Create the file "path" by writing to a temporary file and renaming
+ * it into place. The contents of the file come from "generate", which
+ * should return non-zero if it encounters an error.
+ */
+static int update_info_file(char *path, int (*generate)(FILE *))
+{
+	char *tmp = mkpathdup("%s_XXXXXX", path);
+	int ret = -1;
+	int fd = -1;
+	FILE *fp = NULL;
+
+	safe_create_leading_directories(path);
+	fd = mkstemp(tmp);
+	if (fd < 0)
+		goto out;
+	fp = fdopen(fd, "w");
+	if (!fp)
+		goto out;
+	ret = generate(fp);
+	if (ret)
+		goto out;
+	if (fclose(fp))
+		goto out;
+	if (adjust_shared_perm(tmp) < 0)
+		goto out;
+	if (rename(tmp, path) < 0)
+		goto out;
+	ret = 0;
+
+out:
+	if (ret) {
+		error("unable to update %s: %s", path, strerror(errno));
+		if (fp)
+			fclose(fp);
+		else if (fd >= 0)
+			close(fd);
+		unlink(tmp);
+	}
+	free(tmp);
+	return ret;
+}
 
 static int add_info_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
 {
+	FILE *fp = cb_data;
 	struct object *o = parse_object(sha1);
 	if (!o)
 		return -1;
 
-	fprintf(info_ref_fp, "%s	%s\n", sha1_to_hex(sha1), path);
+	if (fprintf(fp, "%s	%s\n", sha1_to_hex(sha1), path) < 0)
+		return -1;
+
 	if (o->type == OBJ_TAG) {
 		o = deref_tag(o, path, 0);
 		if (o)
-			fprintf(info_ref_fp, "%s	%s^{}\n",
-				sha1_to_hex(o->sha1), path);
+			if (fprintf(fp, "%s	%s^{}\n",
+				sha1_to_hex(o->sha1), path) < 0)
+				return -1;
 	}
 	return 0;
 }
 
+static int generate_info_refs(FILE *fp)
+{
+	return for_each_ref(add_info_ref, fp);
+}
+
 static int update_info_refs(int force)
 {
-	char *path0 = git_pathdup("info/refs");
-	int len = strlen(path0);
-	char *path1 = xmalloc(len + 2);
-
-	strcpy(path1, path0);
-	strcpy(path1 + len, "+");
-
-	safe_create_leading_directories(path0);
-	info_ref_fp = fopen(path1, "w");
-	if (!info_ref_fp)
-		return error("unable to update %s", path1);
-	for_each_ref(add_info_ref, NULL);
-	fclose(info_ref_fp);
-	adjust_shared_perm(path1);
-	rename(path1, path0);
-	free(path0);
-	free(path1);
-	return 0;
+	char *path = git_pathdup("info/refs");
+	int ret = update_info_file(path, generate_info_refs);
+	free(path);
+	return ret;
 }
 
 /* packs */
 static struct pack_info {
 	struct packed_git *p;
 	int old_num;
