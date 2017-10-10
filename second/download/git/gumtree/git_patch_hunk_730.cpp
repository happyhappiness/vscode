 		if (flags & PATHSPEC_KEEP_ORDER)
 			die("BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible");
 		QSORT(pathspec->items, pathspec->nr, pathspec_item_cmp);
 	}
 }
 
-/*
- * N.B. get_pathspec() is deprecated in favor of the "struct pathspec"
- * based interface - see pathspec.c:parse_pathspec().
- *
- * Arguments:
- *  - prefix - a path relative to the root of the working tree
- *  - pathspec - a list of paths underneath the prefix path
- *
- * Iterates over pathspec, prepending each path with prefix,
- * and return the resulting list.
- *
- * If pathspec is empty, return a singleton list containing prefix.
- *
- * If pathspec and prefix are both empty, return an empty list.
- *
- * This is typically used by built-in commands such as add.c, in order
- * to normalize argv arguments provided to the built-in into a list of
- * paths to process, all relative to the root of the working tree.
- */
-const char **get_pathspec(const char *prefix, const char **pathspec)
-{
-	struct pathspec ps;
-	parse_pathspec(&ps,
-		       PATHSPEC_ALL_MAGIC &
-		       ~(PATHSPEC_FROMTOP | PATHSPEC_LITERAL),
-		       PATHSPEC_PREFER_CWD,
-		       prefix, pathspec);
-	return ps._raw;
-}
-
 void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
 {
+	int i;
+
 	*dst = *src;
 	ALLOC_ARRAY(dst->items, dst->nr);
 	COPY_ARRAY(dst->items, src->items, dst->nr);
+
+	for (i = 0; i < dst->nr; i++) {
+		dst->items[i].match = xstrdup(src->items[i].match);
+		dst->items[i].original = xstrdup(src->items[i].original);
+	}
 }
 
 void clear_pathspec(struct pathspec *pathspec)
 {
+	int i;
+
+	for (i = 0; i < pathspec->nr; i++) {
+		free(pathspec->items[i].match);
+		free(pathspec->items[i].original);
+	}
 	free(pathspec->items);
 	pathspec->items = NULL;
+	pathspec->nr = 0;
 }
