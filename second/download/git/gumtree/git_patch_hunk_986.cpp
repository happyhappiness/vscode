 		}
 		strbuf_release(&unquoted);
 		strbuf_release(&buf);
 	}
 
 	if (split_index > 0) {
-		init_split_index(&the_index);
-		the_index.cache_changed |= SPLIT_INDEX_ORDERED;
-	} else if (!split_index && the_index.split_index) {
-		/*
-		 * can't discard_split_index(&the_index); because that
-		 * will destroy split_index->base->cache[], which may
-		 * be shared with the_index.cache[]. So yeah we're
-		 * leaking a bit here.
-		 */
-		the_index.split_index = NULL;
-		the_index.cache_changed |= SOMETHING_CHANGED;
+		if (git_config_get_split_index() == 0)
+			warning(_("core.splitIndex is set to false; "
+				  "remove or change it, if you really want to "
+				  "enable split index"));
+		if (the_index.split_index)
+			the_index.cache_changed |= SPLIT_INDEX_ORDERED;
+		else
+			add_split_index(&the_index);
+	} else if (!split_index) {
+		if (git_config_get_split_index() == 1)
+			warning(_("core.splitIndex is set to true; "
+				  "remove or change it, if you really want to "
+				  "disable split index"));
+		remove_split_index(&the_index);
 	}
 
 	switch (untracked_cache) {
 	case UC_UNSPECIFIED:
 		break;
 	case UC_DISABLE:
