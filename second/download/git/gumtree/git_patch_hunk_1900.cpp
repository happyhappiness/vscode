 		NULL,
 		NULL,
 		NULL,
 		NULL,
 		NULL,
 	};
-	struct child_process po;
+	struct child_process po = CHILD_PROCESS_INIT;
 	int i;
 
 	i = 4;
 	if (args->use_thin_pack)
 		argv[i++] = "--thin";
 	if (args->use_ofs_delta)
 		argv[i++] = "--delta-base-offset";
 	if (args->quiet || !args->progress)
 		argv[i++] = "-q";
 	if (args->progress)
 		argv[i++] = "--progress";
-	memset(&po, 0, sizeof(po));
 	po.argv = argv;
 	po.in = -1;
 	po.out = args->stateless_rpc ? -1 : fd;
 	po.git_cmd = 1;
 	if (start_command(&po))
 		die_errno("git pack-objects failed");
