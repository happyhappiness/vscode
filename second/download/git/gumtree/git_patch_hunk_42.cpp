 		} else
 			return 0;
 
 		item = string_list_insert(&branch_list, name);
 
 		if (!item->util)
-			item->util = xcalloc(sizeof(struct branch_info), 1);
+			item->util = xcalloc(1, sizeof(struct branch_info));
 		info = item->util;
 		if (type == REMOTE) {
 			if (info->remote_name)
 				warning(_("more than one %s"), orig_key);
 			info->remote_name = xstrdup(value);
 		} else if (type == MERGE) {
