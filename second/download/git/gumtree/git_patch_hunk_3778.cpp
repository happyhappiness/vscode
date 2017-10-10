 		if (ren2) {
 			/* One file renamed on both sides */
 			const char *ren2_src = ren2->pair->one->path;
 			const char *ren2_dst = ren2->pair->two->path;
 			enum rename_type rename_type;
 			if (strcmp(ren1_src, ren2_src) != 0)
-				die("ren1_src != ren2_src");
+				die("BUG: ren1_src != ren2_src");
 			ren2->dst_entry->processed = 1;
 			ren2->processed = 1;
 			if (strcmp(ren1_dst, ren2_dst) != 0) {
 				rename_type = RENAME_ONE_FILE_TO_TWO;
 				clean_merge = 0;
 			} else {
