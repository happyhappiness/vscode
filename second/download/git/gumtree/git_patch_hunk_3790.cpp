 			last = dir->entries[i++] = entry;
 	}
 	dir->sorted = dir->nr = i;
 }
 
 /*
- * Return true iff the reference described by entry can be resolved to
- * an object in the database.  Emit a warning if the referred-to
- * object does not exist.
- */
-static int ref_resolves_to_object(struct ref_entry *entry)
+ * Return true if refname, which has the specified oid and flags, can
+ * be resolved to an object in the database. If the referred-to object
+ * does not exist, emit a warning and return false.
+ */
+static int ref_resolves_to_object(const char *refname,
+				  const struct object_id *oid,
+				  unsigned int flags)
 {
-	if (entry->flag & REF_ISBROKEN)
+	if (flags & REF_ISBROKEN)
 		return 0;
-	if (!has_sha1_file(entry->u.value.oid.hash)) {
-		error("%s does not point to a valid object!", entry->name);
+	if (!has_sha1_file(oid->hash)) {
+		error("%s does not point to a valid object!", refname);
 		return 0;
 	}
 	return 1;
 }
 
 /*
- * current_ref is a performance hack: when iterating over references
- * using the for_each_ref*() functions, current_ref is set to the
- * current reference's entry before calling the callback function.  If
- * the callback function calls peel_ref(), then peel_ref() first
- * checks whether the reference to be peeled is the current reference
- * (it usually is) and if so, returns that reference's peeled version
- * if it is available.  This avoids a refname lookup in a common case.
+ * Return true if the reference described by entry can be resolved to
+ * an object in the database; otherwise, emit a warning and return
+ * false.
  */
-static struct ref_entry *current_ref;
-
-typedef int each_ref_entry_fn(struct ref_entry *entry, void *cb_data);
-
-struct ref_entry_cb {
-	const char *base;
-	int trim;
-	int flags;
-	each_ref_fn *fn;
-	void *cb_data;
-};
-
-/*
- * Handle one reference in a do_for_each_ref*()-style iteration,
- * calling an each_ref_fn for each entry.
- */
-static int do_one_ref(struct ref_entry *entry, void *cb_data)
+static int entry_resolves_to_object(struct ref_entry *entry)
 {
-	struct ref_entry_cb *data = cb_data;
-	struct ref_entry *old_current_ref;
-	int retval;
-
-	if (!starts_with(entry->name, data->base))
-		return 0;
-
-	if (!(data->flags & DO_FOR_EACH_INCLUDE_BROKEN) &&
-	      !ref_resolves_to_object(entry))
-		return 0;
-
-	/* Store the old value, in case this is a recursive call: */
-	old_current_ref = current_ref;
-	current_ref = entry;
-	retval = data->fn(entry->name + data->trim, &entry->u.value.oid,
-			  entry->flag, data->cb_data);
-	current_ref = old_current_ref;
-	return retval;
+	return ref_resolves_to_object(entry->name,
+				      &entry->u.value.oid, entry->flag);
 }
 
+typedef int each_ref_entry_fn(struct ref_entry *entry, void *cb_data);
+
 /*
  * Call fn for each reference in dir that has index in the range
  * offset <= index < dir->nr.  Recurse into subdirectories that are in
  * that index range, sorting them before iterating.  This function
  * does not sort dir itself; it should be sorted beforehand.  fn is
  * called for all references, including broken ones.
