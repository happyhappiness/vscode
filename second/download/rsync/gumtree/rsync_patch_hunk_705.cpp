 static void finish_filelist_progress(const struct file_list *flist)
 {
 	if (do_progress) {
 		/* This overwrites the progress line */
 		rprintf(FINFO, "%d file%sto consider\n",
 			flist->count, flist->count == 1 ? " " : "s ");
-	} else {
+	} else
 		rprintf(FINFO, "done\n");
-	}
 }
 
 void show_flist_stats(void)
 {
 	/* Nothing yet */
 }
 
 
-static struct string_area *string_area_new(int size)
-{
-	struct string_area *a;
-
-	if (size <= 0)
-		size = ARENA_SIZE;
-	a = new(struct string_area);
-	if (!a)
-		out_of_memory("string_area_new");
-	a->current = a->base = new_array(char, size);
-	if (!a->current)
-		out_of_memory("string_area_new buffer");
-	a->end = a->base + size;
-	a->next = NULL;
-
-	return a;
-}
-
-static void string_area_free(struct string_area *a)
-{
-	struct string_area *next;
-
-	for (; a; a = next) {
-		next = a->next;
-		free(a->base);
-	}
-}
-
-static char *string_area_malloc(struct string_area **ap, int size)
-{
-	char *p;
-	struct string_area *a;
-
-	/* does the request fit into the current space? */
-	a = *ap;
-	if (a->current + size >= a->end) {
-		/* no; get space, move new string_area to front of the list */
-		a = string_area_new(size > ARENA_SIZE ? size : ARENA_SIZE);
-		a->next = *ap;
-		*ap = a;
-	}
-
-	/* have space; do the "allocation." */
-	p = a->current;
-	a->current += size;
-	return p;
-}
-
-static char *string_area_strdup(struct string_area **ap, const char *src)
-{
-	char *dest = string_area_malloc(ap, strlen(src) + 1);
-	return strcpy(dest, src);
-}
-
 static void list_file_entry(struct file_struct *f)
 {
 	char perms[11];
 
 	if (!f->basename)
 		/* this can happen if duplicate names were removed */
 		return;
 
 	permstring(perms, f->mode);
 
+#if SUPPORT_LINKS
 	if (preserve_links && S_ISLNK(f->mode)) {
 		rprintf(FINFO, "%s %11.0f %s %s -> %s\n",
 			perms,
 			(double) f->length, timestring(f->modtime),
-			f_name(f), f->link);
-	} else {
+			f_name(f), f->u.link);
+	} else
+#endif
 		rprintf(FINFO, "%s %11.0f %s %s\n",
 			perms,
 			(double) f->length, timestring(f->modtime),
 			f_name(f));
-	}
 }
 
 
 /**
  * Stat either a symlink or its referent, depending on the settings of
  * copy_links, copy_unsafe_links, etc.
