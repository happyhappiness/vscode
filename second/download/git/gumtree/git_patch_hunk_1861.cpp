 {
 	cp->count++;
 	if ((cp->count & 1023) == 0)
 		display_progress(cp->progress, cp->count);
 }
 
-static void process_blob(struct blob *blob,
-			 struct object_array *p,
-			 struct name_path *path,
-			 const char *name,
-			 struct connectivity_progress *cp)
-{
-	struct object *obj = &blob->object;
-
-	if (!blob)
-		die("bad blob object");
-	if (obj->flags & SEEN)
-		return;
-	obj->flags |= SEEN;
-	update_progress(cp);
-	/* Nothing to do, really .. The blob lookup was the important part */
+static int add_one_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
+{
+	struct object *object = parse_object_or_die(sha1, path);
+	struct rev_info *revs = (struct rev_info *)cb_data;
+
+	add_pending_object(revs, object, "");
+
+	return 0;
 }
 
-static void process_gitlink(const unsigned char *sha1,
-			    struct object_array *p,
-			    struct name_path *path,
-			    const char *name)
+/*
+ * The traversal will have already marked us as SEEN, so we
+ * only need to handle any progress reporting here.
+ */
+static void mark_object(struct object *obj, const struct name_path *path,
+			const char *name, void *data)
 {
-	/* I don't think we want to recurse into this, really. */
+	update_progress(data);
 }
 
-static void process_tree(struct tree *tree,
-			 struct object_array *p,
-			 struct name_path *path,
-			 const char *name,
-			 struct connectivity_progress *cp)
+static void mark_commit(struct commit *c, void *data)
 {
-	struct object *obj = &tree->object;
-	struct tree_desc desc;
-	struct name_entry entry;
-	struct name_path me;
-
-	if (!tree)
-		die("bad tree object");
-	if (obj->flags & SEEN)
-		return;
-	obj->flags |= SEEN;
-	update_progress(cp);
-	if (parse_tree(tree) < 0)
-		die("bad tree object %s", sha1_to_hex(obj->sha1));
-	add_object(obj, p, path, name);
-	me.up = path;
-	me.elem = name;
-	me.elem_len = strlen(name);
-
-	init_tree_desc(&desc, tree->buffer, tree->size);
-
-	while (tree_entry(&desc, &entry)) {
-		if (S_ISDIR(entry.mode))
-			process_tree(lookup_tree(entry.sha1), p, &me, entry.path, cp);
-		else if (S_ISGITLINK(entry.mode))
-			process_gitlink(entry.sha1, p, &me, entry.path);
-		else
-			process_blob(lookup_blob(entry.sha1), p, &me, entry.path, cp);
-	}
-	free_tree_buffer(tree);
+	mark_object(&c->object, NULL, NULL, data);
 }
 
-static void process_tag(struct tag *tag, struct object_array *p,
-			const char *name, struct connectivity_progress *cp)
+struct recent_data {
+	struct rev_info *revs;
+	unsigned long timestamp;
+};
+
+static void add_recent_object(const unsigned char *sha1,
+			      unsigned long mtime,
+			      struct recent_data *data)
 {
-	struct object *obj = &tag->object;
+	struct object *obj;
+	enum object_type type;
 
-	if (obj->flags & SEEN)
+	if (mtime <= data->timestamp)
 		return;
-	obj->flags |= SEEN;
-	update_progress(cp);
 
-	if (parse_tag(tag) < 0)
-		die("bad tag object %s", sha1_to_hex(obj->sha1));
-	if (tag->tagged)
-		add_object(tag->tagged, p, NULL, name);
-}
-
-static void walk_commit_list(struct rev_info *revs,
-			     struct connectivity_progress *cp)
-{
-	int i;
-	struct commit *commit;
-	struct object_array objects = OBJECT_ARRAY_INIT;
-
-	/* Walk all commits, process their trees */
-	while ((commit = get_revision(revs)) != NULL) {
-		process_tree(commit->tree, &objects, NULL, "", cp);
-		update_progress(cp);
+	/*
+	 * We do not want to call parse_object here, because
+	 * inflating blobs and trees could be very expensive.
+	 * However, we do need to know the correct type for
+	 * later processing, and the revision machinery expects
+	 * commits and tags to have been parsed.
+	 */
+	type = sha1_object_info(sha1, NULL);
+	if (type < 0)
+		die("unable to get object info for %s", sha1_to_hex(sha1));
+
+	switch (type) {
+	case OBJ_TAG:
+	case OBJ_COMMIT:
+		obj = parse_object_or_die(sha1, NULL);
+		break;
+	case OBJ_TREE:
+		obj = (struct object *)lookup_tree(sha1);
+		break;
+	case OBJ_BLOB:
+		obj = (struct object *)lookup_blob(sha1);
+		break;
+	default:
+		die("unknown object type for %s: %s",
+		    sha1_to_hex(sha1), typename(type));
 	}
 
-	/* Then walk all the pending objects, recursively processing them too */
-	for (i = 0; i < revs->pending.nr; i++) {
-		struct object_array_entry *pending = revs->pending.objects + i;
-		struct object *obj = pending->item;
-		const char *name = pending->name;
-		if (obj->type == OBJ_TAG) {
-			process_tag((struct tag *) obj, &objects, name, cp);
-			continue;
-		}
-		if (obj->type == OBJ_TREE) {
-			process_tree((struct tree *)obj, &objects, NULL, name, cp);
-			continue;
-		}
-		if (obj->type == OBJ_BLOB) {
-			process_blob((struct blob *)obj, &objects, NULL, name, cp);
-			continue;
-		}
-		die("unknown pending object %s (%s)", sha1_to_hex(obj->sha1), name);
-	}
-}
+	if (!obj)
+		die("unable to lookup %s", sha1_to_hex(sha1));
 
-static int add_one_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
-		const char *email, unsigned long timestamp, int tz,
-		const char *message, void *cb_data)
-{
-	struct object *object;
-	struct rev_info *revs = (struct rev_info *)cb_data;
-
-	object = parse_object(osha1);
-	if (object)
-		add_pending_object(revs, object, "");
-	object = parse_object(nsha1);
-	if (object)
-		add_pending_object(revs, object, "");
-	return 0;
+	add_pending_object(data->revs, obj, "");
 }
 
-static int add_one_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
+static int add_recent_loose(const unsigned char *sha1,
+			    const char *path, void *data)
 {
-	struct object *object = parse_object_or_die(sha1, path);
-	struct rev_info *revs = (struct rev_info *)cb_data;
+	struct stat st;
+	struct object *obj = lookup_object(sha1);
 
-	add_pending_object(revs, object, "");
+	if (obj && obj->flags & SEEN)
+		return 0;
 
-	return 0;
-}
+	if (stat(path, &st) < 0) {
+		/*
+		 * It's OK if an object went away during our iteration; this
+		 * could be due to a simultaneous repack. But anything else
+		 * we should abort, since we might then fail to mark objects
+		 * which should not be pruned.
+		 */
+		if (errno == ENOENT)
+			return 0;
+		return error("unable to stat %s: %s",
+			     sha1_to_hex(sha1), strerror(errno));
+	}
 
-static int add_one_reflog(const char *path, const unsigned char *sha1, int flag, void *cb_data)
-{
-	for_each_reflog_ent(path, add_one_reflog_ent, cb_data);
+	add_recent_object(sha1, st.st_mtime, data);
 	return 0;
 }
 
-static void add_one_tree(const unsigned char *sha1, struct rev_info *revs)
-{
-	struct tree *tree = lookup_tree(sha1);
-	if (tree)
-		add_pending_object(revs, &tree->object, "");
-}
-
-static void add_cache_tree(struct cache_tree *it, struct rev_info *revs)
-{
-	int i;
-
-	if (it->entry_count >= 0)
-		add_one_tree(it->sha1, revs);
-	for (i = 0; i < it->subtree_nr; i++)
-		add_cache_tree(it->down[i]->cache_tree, revs);
+static int add_recent_packed(const unsigned char *sha1,
+			     struct packed_git *p, uint32_t pos,
+			     void *data)
+{
+	struct object *obj = lookup_object(sha1);
+
+	if (obj && obj->flags & SEEN)
+		return 0;
+	add_recent_object(sha1, p->mtime, data);
+	return 0;
 }
 
-static void add_cache_refs(struct rev_info *revs)
+int add_unseen_recent_objects_to_traversal(struct rev_info *revs,
+					   unsigned long timestamp)
 {
-	int i;
+	struct recent_data data;
+	int r;
 
-	read_cache();
-	for (i = 0; i < active_nr; i++) {
-		/*
-		 * The index can contain blobs and GITLINKs, GITLINKs are hashes
-		 * that don't actually point to objects in the repository, it's
-		 * almost guaranteed that they are NOT blobs, so we don't call
-		 * lookup_blob() on them, to avoid populating the hash table
-		 * with invalid information
-		 */
-		if (S_ISGITLINK(active_cache[i]->ce_mode))
-			continue;
+	data.revs = revs;
+	data.timestamp = timestamp;
 
-		lookup_blob(active_cache[i]->sha1);
-		/*
-		 * We could add the blobs to the pending list, but quite
-		 * frankly, we don't care. Once we've looked them up, and
-		 * added them as objects, we've really done everything
-		 * there is to do for a blob
-		 */
-	}
-	if (active_cache_tree)
-		add_cache_tree(active_cache_tree, revs);
+	r = for_each_loose_object(add_recent_loose, &data);
+	if (r)
+		return r;
+	return for_each_packed_object(add_recent_packed, &data);
 }
 
 void mark_reachable_objects(struct rev_info *revs, int mark_reflog,
+			    unsigned long mark_recent,
 			    struct progress *progress)
 {
 	struct connectivity_progress cp;
 
 	/*
 	 * Set up revision parsing, and mark us as being interested
