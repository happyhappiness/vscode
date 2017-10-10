 	if (!strcmp(var, "core.createobject")) {
 		if (!strcmp(value, "rename"))
 			object_creation_mode = OBJECT_CREATION_USES_RENAMES;
 		else if (!strcmp(value, "link"))
 			object_creation_mode = OBJECT_CREATION_USES_HARDLINKS;
 		else
-			die("Invalid mode for object creation: %s", value);
+			die(_("invalid mode for object creation: %s"), value);
 		return 0;
 	}
 
 	if (!strcmp(var, "core.sparsecheckout")) {
 		core_apply_sparse_checkout = git_config_bool(var, value);
 		return 0;
