 		clean_pack_garbage();
 
 	if (auto_gc && too_many_loose_objects())
 		warning(_("There are too many unreachable loose objects; "
 			"run 'git prune' to remove them."));
 
+	if (!daemonized)
+		unlink(git_path("gc.log"));
+
 	return 0;
 }
