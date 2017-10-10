 		return error("%s: object corrupt or missing", sha1_to_hex(sha1));
 	}
 	obj->flags = HAS_OBJ;
 	return fsck_obj(obj);
 }
 
-/*
- * This is the sorting chunk size: make it reasonably
- * big so that we can sort well..
- */
-#define MAX_SHA1_ENTRIES (1024)
-
-struct sha1_entry {
-	unsigned long ino;
-	unsigned char sha1[20];
-};
-
-static struct {
-	unsigned long nr;
-	struct sha1_entry *entry[MAX_SHA1_ENTRIES];
-} sha1_list;
-
-static int ino_compare(const void *_a, const void *_b)
-{
-	const struct sha1_entry *a = _a, *b = _b;
-	unsigned long ino1 = a->ino, ino2 = b->ino;
-	return ino1 < ino2 ? -1 : ino1 > ino2 ? 1 : 0;
-}
-
-static void fsck_sha1_list(void)
-{
-	int i, nr = sha1_list.nr;
-
-	if (SORT_DIRENT)
-		qsort(sha1_list.entry, nr,
-		      sizeof(struct sha1_entry *), ino_compare);
-	for (i = 0; i < nr; i++) {
-		struct sha1_entry *entry = sha1_list.entry[i];
-		unsigned char *sha1 = entry->sha1;
-
-		sha1_list.entry[i] = NULL;
-		if (fsck_sha1(sha1))
-			errors_found |= ERROR_OBJECT;
-		free(entry);
-	}
-	sha1_list.nr = 0;
-}
-
-static void add_sha1_list(unsigned char *sha1, unsigned long ino)
-{
-	struct sha1_entry *entry = xmalloc(sizeof(*entry));
-	int nr;
-
-	entry->ino = ino;
-	hashcpy(entry->sha1, sha1);
-	nr = sha1_list.nr;
-	if (nr == MAX_SHA1_ENTRIES) {
-		fsck_sha1_list();
-		nr = 0;
-	}
-	sha1_list.entry[nr] = entry;
-	sha1_list.nr = ++nr;
-}
-
-static inline int is_loose_object_file(struct dirent *de,
-				       char *name, unsigned char *sha1)
-{
-	if (strlen(de->d_name) != 38)
-		return 0;
-	memcpy(name + 2, de->d_name, 39);
-	return !get_sha1_hex(name, sha1);
-}
-
-static void fsck_dir(int i, char *path)
-{
-	DIR *dir = opendir(path);
-	struct dirent *de;
-	char name[100];
-
-	if (!dir)
-		return;
-
-	if (verbose)
-		fprintf(stderr, "Checking directory %s\n", path);
-
-	sprintf(name, "%02x", i);
-	while ((de = readdir(dir)) != NULL) {
-		unsigned char sha1[20];
-
-		if (is_dot_or_dotdot(de->d_name))
-			continue;
-		if (is_loose_object_file(de, name, sha1)) {
-			add_sha1_list(sha1, DIRENT_SORT_HINT(de));
-			continue;
-		}
-		if (starts_with(de->d_name, "tmp_obj_"))
-			continue;
-		fprintf(stderr, "bad sha1 file: %s/%s\n", path, de->d_name);
-	}
-	closedir(dir);
-}
-
 static int default_refs;
 
 static void fsck_handle_reflog_sha1(const char *refname, unsigned char *sha1)
 {
 	struct object *obj;
 
