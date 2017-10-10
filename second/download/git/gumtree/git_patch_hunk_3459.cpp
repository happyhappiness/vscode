 
 static int do_generic_cmd(const char *me, char *arg)
 {
 	const char *my_argv[4];
 
 	setup_path();
-	if (!arg || !(arg = sq_dequote(arg)) || *arg == '-')
+	if (!arg || !(arg = sq_dequote(arg)))
 		die("bad argument");
 	if (!starts_with(me, "git-"))
 		die("bad command");
 
 	my_argv[0] = me + 4;
 	my_argv[1] = arg;
