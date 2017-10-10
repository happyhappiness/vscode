 	    (unpack_unreachable || (pack_everything & LOOSEN_UNREACHABLE)))
 		die(_("--keep-unreachable and -A are incompatible"));
 
 	if (pack_kept_objects < 0)
 		pack_kept_objects = write_bitmaps;
 
+	if (write_bitmaps && !(pack_everything & ALL_INTO_ONE))
+		die(_(incremental_bitmap_conflict_error));
+
 	packdir = mkpathdup("%s/pack", get_object_directory());
 	packtmp = mkpathdup("%s/.tmp-%d-pack", packdir, (int)getpid());
 
 	sigchain_push_common(remove_pack_on_signal);
 
 	argv_array_push(&cmd.args, "pack-objects");
