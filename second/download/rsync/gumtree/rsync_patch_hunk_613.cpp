 	batch_flist->count = 0;
 	batch_flist->malloced = 1000;
 	batch_flist->files =
 	    (struct file_struct **) malloc(sizeof(batch_flist->files[0]) *
 					   batch_flist->malloced);
 	if (!batch_flist->files) {
-		out_of_memory("create_flist_from_batch");	/* dw -- will exit */
+		out_of_memory("create_flist_from_batch");
 	}
 
 	for (flags = read_batch_flags(); flags; flags = read_batch_flags()) {
 
 		int i = batch_flist->count;
 
