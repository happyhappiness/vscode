 		chosen = list_and_choose(&menu_opts, &menu_stuff);
 
 		if (*chosen != EOF) {
 			int ret;
 			ret = menus[*chosen].fn();
 			if (ret != MENU_RETURN_NO_LOOP) {
-				free(chosen);
-				chosen = NULL;
+				FREE_AND_NULL(chosen);
 				if (!del_list.nr) {
 					clean_print_color(CLEAN_COLOR_ERROR);
 					printf_ln(_("No more files to clean, exiting."));
 					clean_print_color(CLEAN_COLOR_RESET);
 					break;
 				}
 				continue;
 			}
 		} else {
 			quit_cmd();
 		}
 
-		free(chosen);
-		chosen = NULL;
+		FREE_AND_NULL(chosen);
 		break;
 	}
 }
 
 static void correct_untracked_entries(struct dir_struct *dir)
 {
