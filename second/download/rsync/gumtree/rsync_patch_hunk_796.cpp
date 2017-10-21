 
 void init_hard_links(void)
 {
 #ifdef SUPPORT_HARD_LINKS
 	int i;
 
-	if (the_file_list->count < 2)
-		return;
-
 	if (hlink_list)
 		free(hlink_list);
 
 	if (!(hlink_list = new_array(int, the_file_list->count)))
 		out_of_memory("init_hard_links");
 
