 
 	if (!pack_to_stdout && thin)
 		die("--thin cannot be used to build an indexable pack.");
 
 	if (keep_unreachable && unpack_unreachable)
 		die("--keep-unreachable and --unpack-unreachable are incompatible.");
+	if (!rev_list_all || !rev_list_reflog || !rev_list_index)
+		unpack_unreachable_expiration = 0;
 
 	if (!use_internal_rev_list || !pack_to_stdout || is_repository_shallow())
 		use_bitmap_index = 0;
 
 	if (pack_to_stdout || !rev_list_all)
 		write_bitmap_index = 0;
