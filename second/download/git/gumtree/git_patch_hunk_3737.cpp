 		msg_type = FSCK_WARN;
 
 	append_msg_id(&sb, msg_id_info[id].id_string);
 
 	va_start(ap, fmt);
 	strbuf_vaddf(&sb, fmt, ap);
-	result = options->error_func(object, msg_type, sb.buf);
+	result = options->error_func(options, object, msg_type, sb.buf);
 	strbuf_release(&sb);
 	va_end(ap);
 
 	return result;
 }
 
+static char *get_object_name(struct fsck_options *options, struct object *obj)
+{
+	if (!options->object_names)
+		return NULL;
+	return lookup_decoration(options->object_names, obj);
+}
+
+static void put_object_name(struct fsck_options *options, struct object *obj,
+	const char *fmt, ...)
+{
+	va_list ap;
+	struct strbuf buf = STRBUF_INIT;
+	char *existing;
+
+	if (!options->object_names)
+		return;
+	existing = lookup_decoration(options->object_names, obj);
+	if (existing)
+		return;
+	va_start(ap, fmt);
+	strbuf_vaddf(&buf, fmt, ap);
+	add_decoration(options->object_names, obj, strbuf_detach(&buf, NULL));
+	va_end(ap);
+}
+
+static const char *describe_object(struct fsck_options *o, struct object *obj)
+{
+	static struct strbuf buf = STRBUF_INIT;
+	char *name;
+
+	strbuf_reset(&buf);
+	strbuf_addstr(&buf, oid_to_hex(&obj->oid));
+	if (o->object_names && (name = lookup_decoration(o->object_names, obj)))
+		strbuf_addf(&buf, " (%s)", name);
+
+	return buf.buf;
+}
+
 static int fsck_walk_tree(struct tree *tree, void *data, struct fsck_options *options)
 {
 	struct tree_desc desc;
 	struct name_entry entry;
 	int res = 0;
+	const char *name;
 
 	if (parse_tree(tree))
 		return -1;
 
+	name = get_object_name(options, &tree->object);
 	init_tree_desc(&desc, tree->buffer, tree->size);
 	while (tree_entry(&desc, &entry)) {
+		struct object *obj;
 		int result;
 
 		if (S_ISGITLINK(entry.mode))
 			continue;
-		if (S_ISDIR(entry.mode))
-			result = options->walk(&lookup_tree(entry.oid->hash)->object, OBJ_TREE, data, options);
-		else if (S_ISREG(entry.mode) || S_ISLNK(entry.mode))
-			result = options->walk(&lookup_blob(entry.oid->hash)->object, OBJ_BLOB, data, options);
+
+		if (S_ISDIR(entry.mode)) {
+			obj = &lookup_tree(entry.oid->hash)->object;
+			if (name)
+				put_object_name(options, obj, "%s%s/", name,
+					entry.path);
+			result = options->walk(obj, OBJ_TREE, data, options);
+		}
+		else if (S_ISREG(entry.mode) || S_ISLNK(entry.mode)) {
+			obj = &lookup_blob(entry.oid->hash)->object;
+			if (name)
+				put_object_name(options, obj, "%s%s", name,
+					entry.path);
+			result = options->walk(obj, OBJ_BLOB, data, options);
+		}
 		else {
 			result = error("in tree %s: entry %s has bad mode %.6o",
-					oid_to_hex(&tree->object.oid), entry.path, entry.mode);
+					describe_object(options, &tree->object), entry.path, entry.mode);
 		}
 		if (result < 0)
 			return result;
 		if (!res)
 			res = result;
 	}
 	return res;
 }
 
 static int fsck_walk_commit(struct commit *commit, void *data, struct fsck_options *options)
 {
+	int counter = 0, generation = 0, name_prefix_len = 0;
 	struct commit_list *parents;
 	int res;
 	int result;
+	const char *name;
 
 	if (parse_commit(commit))
 		return -1;
 
+	name = get_object_name(options, &commit->object);
+	if (name)
+		put_object_name(options, &commit->tree->object, "%s:", name);
+
 	result = options->walk((struct object *)commit->tree, OBJ_TREE, data, options);
 	if (result < 0)
 		return result;
 	res = result;
 
 	parents = commit->parents;
+	if (name && parents) {
+		int len = strlen(name), power;
+
+		if (len && name[len - 1] == '^') {
+			generation = 1;
+			name_prefix_len = len - 1;
+		}
+		else { /* parse ~<generation> suffix */
+			for (generation = 0, power = 1;
+			     len && isdigit(name[len - 1]);
+			     power *= 10)
+				generation += power * (name[--len] - '0');
+			if (power > 1 && len && name[len - 1] == '~')
+				name_prefix_len = len - 1;
+		}
+	}
+
 	while (parents) {
+		if (name) {
+			struct object *obj = &parents->item->object;
+
+			if (++counter > 1)
+				put_object_name(options, obj, "%s^%d",
+					name, counter);
+			else if (generation > 0)
+				put_object_name(options, obj, "%.*s~%d",
+					name_prefix_len, name, generation + 1);
+			else
+				put_object_name(options, obj, "%s^", name);
+		}
 		result = options->walk((struct object *)parents->item, OBJ_COMMIT, data, options);
 		if (result < 0)
 			return result;
 		if (!res)
 			res = result;
 		parents = parents->next;
 	}
 	return res;
 }
 
 static int fsck_walk_tag(struct tag *tag, void *data, struct fsck_options *options)
 {
+	char *name = get_object_name(options, &tag->object);
+
 	if (parse_tag(tag))
 		return -1;
+	if (name)
+		put_object_name(options, tag->tagged, "%s", name);
 	return options->walk(tag->tagged, OBJ_ANY, data, options);
 }
 
 int fsck_walk(struct object *obj, void *data, struct fsck_options *options)
 {
 	if (!obj)
