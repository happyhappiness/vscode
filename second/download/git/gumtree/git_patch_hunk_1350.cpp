 	}
 }
 
 int cmd_remote_ext(int argc, const char **argv, const char *prefix)
 {
 	if (argc != 3)
-		die("Expected two arguments");
+		usage(usage_msg);
 
 	return command_loop(argv[2]);
 }
