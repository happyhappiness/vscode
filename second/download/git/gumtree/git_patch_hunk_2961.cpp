 
 	return 0;
 }
 
 static char *pack_bitmap_filename(struct packed_git *p)
 {
-	char *idx_name;
-	int len;
-
-	len = strlen(p->pack_name) - strlen(".pack");
-	idx_name = xmalloc(len + strlen(".bitmap") + 1);
-
-	memcpy(idx_name, p->pack_name, len);
-	memcpy(idx_name + len, ".bitmap", strlen(".bitmap") + 1);
+	size_t len;
 
-	return idx_name;
+	if (!strip_suffix(p->pack_name, ".pack", &len))
+		die("BUG: pack_name does not end in .pack");
+	return xstrfmt("%.*s.bitmap", (int)len, p->pack_name);
 }
 
 static int open_pack_bitmap_1(struct packed_git *packfile)
 {
 	int fd;
 	struct stat st;
