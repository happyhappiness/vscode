@@ -128,6 +128,9 @@ struct mtree_entry {
 	unsigned long fflags_clear;
 	dev_t rdevmajor;
 	dev_t rdevminor;
+	dev_t devmajor;
+	dev_t devminor;
+	int64_t ino;
 };
 
 struct mtree_writer {
@@ -210,6 +213,9 @@ struct mtree_writer {
 #define	F_SHA256	0x00800000		/* SHA-256 digest */
 #define	F_SHA384	0x01000000		/* SHA-384 digest */
 #define	F_SHA512	0x02000000		/* SHA-512 digest */
+#define	F_INO		0x04000000		/* inode number */
+#define	F_RESDEV	0x08000000		/* device ID on which the
+						 * entry resides */
 
 	/* Options */
 	int dironly;		/* If it is set, ignore all files except
@@ -823,8 +829,11 @@ mtree_entry_new(struct archive_write *a, struct archive_entry *entry,
 	archive_entry_fflags(entry, &me->fflags_set, &me->fflags_clear);
 	me->mtime = archive_entry_mtime(entry);
 	me->mtime_nsec = archive_entry_mtime_nsec(entry);
-	me->rdevmajor =	archive_entry_rdevmajor(entry);
+	me->rdevmajor = archive_entry_rdevmajor(entry);
 	me->rdevminor = archive_entry_rdevminor(entry);
+	me->devmajor = archive_entry_devmajor(entry);
+	me->devminor = archive_entry_devminor(entry);
+	me->ino = archive_entry_ino(entry);
 	me->size = archive_entry_size(entry);
 	if (me->filetype == AE_IFDIR) {
 		me->dir_info = calloc(1, sizeof(*me->dir_info));
@@ -882,7 +891,7 @@ archive_write_mtree_header(struct archive_write *a,
 		mtree->first = 0;
 		archive_strcat(&mtree->buf, "#mtree\n");
 		if ((mtree->keys & SET_KEYS) == 0)
-			mtree->output_global_set = 0;/* Disalbed. */
+			mtree->output_global_set = 0;/* Disabled. */
 	}
 
 	mtree->entry_bytes_remaining = archive_entry_size(entry);
@@ -983,6 +992,15 @@ write_mtree_entry(struct archive_write *a, struct mtree_entry *me)
 	if ((keys & F_UID) != 0)
 		archive_string_sprintf(str, " uid=%jd", (intmax_t)me->uid);
 
+	if ((keys & F_INO) != 0)
+		archive_string_sprintf(str, " inode=%jd", (intmax_t)me->ino);
+	if ((keys & F_RESDEV) != 0) {
+		archive_string_sprintf(str,
+		    " resdevice=native,%ju,%ju",
+		    (uintmax_t)me->devmajor,
+		    (uintmax_t)me->devminor);
+	}
+
 	switch (me->filetype) {
 	case AE_IFLNK:
 		if ((keys & F_TYPE) != 0)
@@ -1117,7 +1135,7 @@ write_mtree_entry_tree(struct archive_write *a)
 		} else {
 			/* Whenever output_global_set is enabled
 			 * output global value(/set keywords)
-			 * even if the directory entry is not allowd
+			 * even if the directory entry is not allowed
 			 * to be written because the global values
 			 * can be used for the children. */
 			if (mtree->output_global_set)
@@ -1296,6 +1314,8 @@ archive_write_mtree_options(struct archive_write *a, const char *key,
 		if (strcmp(key, "indent") == 0) {
 			mtree->indent = (value != NULL)? 1: 0;
 			return (ARCHIVE_OK);
+		} else if (strcmp(key, "inode") == 0) {
+			keybit = F_INO;
 		}
 		break;
 	case 'l':
@@ -1314,7 +1334,9 @@ archive_write_mtree_options(struct archive_write *a, const char *key,
 			keybit = F_NLINK;
 		break;
 	case 'r':
-		if (strcmp(key, "ripemd160digest") == 0 ||
+		if (strcmp(key, "resdevice") == 0) {
+			keybit = F_RESDEV;
+		} else if (strcmp(key, "ripemd160digest") == 0 ||
 		    strcmp(key, "rmd160") == 0 ||
 		    strcmp(key, "rmd160digest") == 0)
 			keybit = F_RMD160;
@@ -1855,9 +1877,9 @@ mtree_entry_setup_filenames(struct archive_write *a, struct mtree_entry *file,
 		return (ret);
 	}
 
-	/* Make a basename from dirname and slash */
+	/* Make a basename from file->parentdir.s and slash */
 	*slash  = '\0';
-	file->parentdir.length = slash - dirname;
+	file->parentdir.length = slash - file->parentdir.s;
 	archive_strcpy(&(file->basename),  slash + 1);
 	return (ret);
 }
@@ -2198,6 +2220,9 @@ mtree_entry_exchange_same_entry(struct archive_write *a, struct mtree_entry *np,
 	np->mtime_nsec = file->mtime_nsec;
 	np->rdevmajor = file->rdevmajor;
 	np->rdevminor = file->rdevminor;
+	np->devmajor = file->devmajor;
+	np->devminor = file->devminor;
+	np->ino = file->ino;
 
 	return (ARCHIVE_WARN);
 }