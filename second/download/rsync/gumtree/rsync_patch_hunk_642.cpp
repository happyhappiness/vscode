 
 		if (i >= batch_flist->malloced) {
 			if (batch_flist->malloced < 1000)
 				batch_flist->malloced += 1000;
 			else
 				batch_flist->malloced *= 2;
-			batch_flist->files =
-			    (struct file_struct **) realloc(batch_flist->
-							    files,
-							    sizeof
-							    (batch_flist->
-							     files[0]) *
-							    batch_flist->
-							    malloced);
+			batch_flist->files
+				= realloc_array(batch_flist->files,
+						struct file_struct *,
+						batch_flist->malloced);
 			if (!batch_flist->files)
 				out_of_memory("create_flist_from_batch");
 		}
 		read_batch_flist_info(&batch_flist->files[i]);
 		batch_flist->files[i]->flags = flags;
 
