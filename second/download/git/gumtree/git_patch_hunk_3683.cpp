 			add_object_entry(o->oid.hash, o->type, "", 0);
 		}
 	}
 	free(in_pack.array);
 }
 
+static int add_loose_object(const unsigned char *sha1, const char *path,
+			    void *data)
+{
+	enum object_type type = sha1_object_info(sha1, NULL);
+
+	if (type < 0) {
+		warning("loose object at %s could not be examined", path);
+		return 0;
+	}
+
+	add_object_entry(sha1, type, "", 0);
+	return 0;
+}
+
+/*
+ * We actually don't even have to worry about reachability here.
+ * add_object_entry will weed out duplicates, so we just add every
+ * loose object we find.
+ */
+static void add_unreachable_loose_objects(void)
+{
+	for_each_loose_file_in_objdir(get_object_directory(),
+				      add_loose_object,
+				      NULL, NULL, NULL);
+}
+
 static int has_sha1_pack_kept_or_nonlocal(const unsigned char *sha1)
 {
 	static struct packed_git *last_found = (void *)1;
 	struct packed_git *p;
 
 	p = (last_found != (void *)1) ? last_found : packed_git;
