 
 unmap:
 	munmap(mmap, mmap_size);
 	die("index file corrupt");
 }
 
+int read_index_from(struct index_state *istate, const char *path)
+{
+	struct split_index *split_index;
+	int ret;
+
+	/* istate->initialized covers both .git/index and .git/sharedindex.xxx */
+	if (istate->initialized)
+		return istate->cache_nr;
+
+	ret = do_read_index(istate, path, 0);
+	split_index = istate->split_index;
+	if (!split_index)
+		return ret;
+
+	if (is_null_sha1(split_index->base_sha1))
+		return ret;
+
+	if (split_index->base)
+		discard_index(split_index->base);
+	else
+		split_index->base = xcalloc(1, sizeof(*split_index->base));
+	ret = do_read_index(split_index->base,
+			    git_path("sharedindex.%s",
+				     sha1_to_hex(split_index->base_sha1)), 1);
+	if (hashcmp(split_index->base_sha1, split_index->base->sha1))
+		die("broken index, expect %s in %s, got %s",
+		    sha1_to_hex(split_index->base_sha1),
+		    git_path("sharedindex.%s",
+				     sha1_to_hex(split_index->base_sha1)),
+		    sha1_to_hex(split_index->base->sha1));
+	merge_base_index(istate);
+	return ret;
+}
+
 int is_index_unborn(struct index_state *istate)
 {
 	return (!istate->cache_nr && !istate->timestamp.sec);
 }
 
 int discard_index(struct index_state *istate)
 {
 	int i;
 
-	for (i = 0; i < istate->cache_nr; i++)
+	for (i = 0; i < istate->cache_nr; i++) {
+		if (istate->cache[i]->index &&
+		    istate->split_index &&
+		    istate->split_index->base &&
+		    istate->cache[i]->index <= istate->split_index->base->cache_nr &&
+		    istate->cache[i] == istate->split_index->base->cache[istate->cache[i]->index - 1])
+			continue;
 		free(istate->cache[i]);
+	}
 	resolve_undo_clear_index(istate);
 	istate->cache_nr = 0;
 	istate->cache_changed = 0;
 	istate->timestamp.sec = 0;
 	istate->timestamp.nsec = 0;
 	free_name_hash(istate);
 	cache_tree_free(&(istate->cache_tree));
 	istate->initialized = 0;
 	free(istate->cache);
 	istate->cache = NULL;
 	istate->cache_alloc = 0;
+	discard_split_index(istate);
 	return 0;
 }
 
 int unmerged_index(const struct index_state *istate)
 {
 	int i;
