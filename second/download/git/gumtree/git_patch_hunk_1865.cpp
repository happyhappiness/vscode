 
 		*ent_size = (name - ((char *)ondisk)) + consumed;
 	}
 	return ce;
 }
 
+static void check_ce_order(struct cache_entry *ce, struct cache_entry *next_ce)
+{
+	int name_compare = strcmp(ce->name, next_ce->name);
+	if (0 < name_compare)
+		die("unordered stage entries in index");
+	if (!name_compare) {
+		if (!ce_stage(ce))
+			die("multiple stage entries for merged file '%s'",
+				ce->name);
+		if (ce_stage(ce) > ce_stage(next_ce))
+			die("unordered stage entries for '%s'",
+				ce->name);
+	}
+}
+
 /* remember to discard_cache() before reading a different cache! */
 int do_read_index(struct index_state *istate, const char *path, int must_exist)
 {
 	int fd, i;
 	struct stat st;
 	unsigned long src_offset;
