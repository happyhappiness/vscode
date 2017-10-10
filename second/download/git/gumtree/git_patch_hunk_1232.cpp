 	if (sb->final_buf_size && cp[-1] != '\n')
 		putchar('\n');
 
 	commit_info_destroy(&ci);
 }
 
-static void output(struct scoreboard *sb, int option)
+static void output(struct blame_scoreboard *sb, int option)
 {
 	struct blame_entry *ent;
 
 	if (option & OUTPUT_PORCELAIN) {
 		for (ent = sb->ent; ent; ent = ent->next) {
 			int count = 0;
-			struct origin *suspect;
+			struct blame_origin *suspect;
 			struct commit *commit = ent->suspect->commit;
 			if (commit->object.flags & MORE_THAN_ONE_PATH)
 				continue;
 			for (suspect = commit->util; suspect; suspect = suspect->next) {
 				if (suspect->guilty && count++) {
 					commit->object.flags |= MORE_THAN_ONE_PATH;
