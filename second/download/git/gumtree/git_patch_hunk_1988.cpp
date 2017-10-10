 		string_list_append(&names, line.buf);
 	}
 	fclose(out);
 	ret = finish_command(&cmd);
 	if (ret)
 		return ret;
-	argv_array_clear(&cmd_args);
 
 	if (!names.nr && !quiet)
 		printf("Nothing new to pack.\n");
 
 	/*
 	 * Ok we have prepared all new packfiles.
