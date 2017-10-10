 		exit(code);
 
 	data->helper = helper;
 	data->no_disconnect_req = 0;
 
 	/*
-	 * Open the output as FILE* so strbuf_getline() can be used.
+	 * Open the output as FILE* so strbuf_getline_*() family of
+	 * functions can be used.
 	 * Do this with duped fd because fclose() will close the fd,
 	 * and stuff like taking over will require the fd to remain.
 	 */
 	duped = dup(helper->out);
 	if (duped < 0)
 		die_errno("Can't dup helper output fd");
