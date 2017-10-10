 	if (use_include_tag)
 		argv_array_push(&pack_objects.args, "--include-tag");
 
 	pack_objects.in = -1;
 	pack_objects.out = -1;
 	pack_objects.err = -1;
-	pack_objects.git_cmd = 1;
 
 	if (start_command(&pack_objects))
 		die("git upload-pack: unable to fork git-pack-objects");
 
 	pipe_fd = xfdopen(pack_objects.in, "w");
 
