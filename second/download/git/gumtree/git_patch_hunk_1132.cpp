 		name += 10;
 	printf("tag %s\nfrom :%d\n%.*s%sdata %d\n%.*s\n",
 	       name, tagged_mark,
 	       (int)(tagger_end - tagger), tagger,
 	       tagger == tagger_end ? "" : "\n",
 	       (int)message_size, (int)message_size, message ? message : "");
+	free(buf);
 }
 
 static struct commit *get_commit(struct rev_cmdline_entry *e, char *full_name)
 {
 	switch (e->item->type) {
 	case OBJ_COMMIT:
