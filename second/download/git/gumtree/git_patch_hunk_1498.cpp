 			item->flags |= PATHSPEC_ONESTAR;
 	}
 
 	/* sanity checks, pathspec matchers assume these are sane */
 	if (item->nowildcard_len > item->len ||
 	    item->prefix         > item->len) {
-		/*
-		 * This case can be triggered by the user pointing us to a
-		 * pathspec inside a submodule, which is an input error.
-		 * Detect that here and complain, but fallback in the
-		 * non-submodule case to a BUG, as we have no idea what
-		 * would trigger that.
-		 */
-		die_inside_submodule_path(item);
-		die ("BUG: item->nowildcard_len > item->len || item->prefix > item->len)");
+		die ("BUG: error initializing pathspec_item");
 	}
 }
 
 static int pathspec_item_cmp(const void *a_, const void *b_)
 {
 	struct pathspec_item *a, *b;
