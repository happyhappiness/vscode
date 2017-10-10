 		dirlen = last_slash - path;
 	} else {
 		basename_offset = 0;
 		dirlen = 0;
 	}
 
-	prepare_attr_stack(path, dirlen);
-	for (i = 0; i < attr_nr; i++)
-		check_all_attr[i].value = ATTR__UNKNOWN;
-	if (num && !cannot_trust_maybe_real) {
+	prepare_attr_stack(path, dirlen, &check->stack);
+	all_attrs_init(&g_attr_hashmap, check);
+	determine_macros(check->all_attrs, check->stack);
+
+	if (check->nr) {
 		rem = 0;
-		for (i = 0; i < num; i++) {
-			if (!check[i].attr->maybe_real) {
-				struct git_attr_check *c;
-				c = check_all_attr + check[i].attr->attr_nr;
-				c->value = ATTR__UNSET;
+		for (i = 0; i < check->nr; i++) {
+			int n = check->items[i].attr->attr_nr;
+			struct all_attrs_item *item = &check->all_attrs[n];
+			if (item->macro) {
+				item->value = ATTR__UNSET;
 				rem++;
 			}
 		}
-		if (rem == num)
+		if (rem == check->nr)
 			return;
 	}
 
-	rem = attr_nr;
-	for (stk = attr_stack; 0 < rem && stk; stk = stk->prev)
-		rem = fill(path, pathlen, basename_offset, stk, rem);
+	rem = check->all_attrs_nr;
+	fill(path, pathlen, basename_offset, check->stack, check->all_attrs, rem);
 }
 
-int git_check_attr(const char *path, int num, struct git_attr_check *check)
+int git_check_attr(const char *path, struct attr_check *check)
 {
 	int i;
 
-	collect_some_attrs(path, num, check);
+	collect_some_attrs(path, check);
 
-	for (i = 0; i < num; i++) {
-		const char *value = check_all_attr[check[i].attr->attr_nr].value;
+	for (i = 0; i < check->nr; i++) {
+		size_t n = check->items[i].attr->attr_nr;
+		const char *value = check->all_attrs[n].value;
 		if (value == ATTR__UNKNOWN)
 			value = ATTR__UNSET;
-		check[i].value = value;
+		check->items[i].value = value;
 	}
 
 	return 0;
 }
 
-int git_all_attrs(const char *path, int *num, struct git_attr_check **check)
+void git_all_attrs(const char *path, struct attr_check *check)
 {
-	int i, count, j;
+	int i;
 
-	collect_some_attrs(path, 0, NULL);
+	attr_check_reset(check);
+	collect_some_attrs(path, check);
 
-	/* Count the number of attributes that are set. */
-	count = 0;
-	for (i = 0; i < attr_nr; i++) {
-		const char *value = check_all_attr[i].value;
-		if (value != ATTR__UNSET && value != ATTR__UNKNOWN)
-			++count;
-	}
-	*num = count;
-	ALLOC_ARRAY(*check, count);
-	j = 0;
-	for (i = 0; i < attr_nr; i++) {
-		const char *value = check_all_attr[i].value;
-		if (value != ATTR__UNSET && value != ATTR__UNKNOWN) {
-			(*check)[j].attr = check_all_attr[i].attr;
-			(*check)[j].value = value;
-			++j;
-		}
+	for (i = 0; i < check->all_attrs_nr; i++) {
+		const char *name = check->all_attrs[i].attr->name;
+		const char *value = check->all_attrs[i].value;
+		struct attr_check_item *item;
+		if (value == ATTR__UNSET || value == ATTR__UNKNOWN)
+			continue;
+		item = attr_check_append(check, git_attr(name));
+		item->value = value;
 	}
-
-	return 0;
 }
 
-void git_attr_set_direction(enum git_attr_direction new, struct index_state *istate)
+void attr_start(void)
 {
-	enum git_attr_direction old = direction;
-
-	if (is_bare_repository() && new != GIT_ATTR_INDEX)
-		die("BUG: non-INDEX attr direction in a bare repo");
-
-	direction = new;
-	if (new != old)
-		drop_attr_stack();
-	use_index = istate;
+#ifndef NO_PTHREADS
+	pthread_mutex_init(&g_attr_hashmap.mutex, NULL);
+	pthread_mutex_init(&check_vector.mutex, NULL);
+#endif
 }
