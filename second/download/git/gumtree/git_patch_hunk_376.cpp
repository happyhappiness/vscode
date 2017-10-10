 	if (numbered && keep_subject && !numbered_cmdline_opt)
 		numbered = 0;
 
 	if (numbered && keep_subject)
 		die (_("-n and -k are mutually exclusive."));
 	if (keep_subject && subject_prefix)
-		die (_("--subject-prefix and -k are mutually exclusive."));
+		die (_("--subject-prefix/--rfc and -k are mutually exclusive."));
 	rev.preserve_subject = keep_subject;
 
 	argc = setup_revisions(argc, argv, &rev, &s_r_opt);
 	if (argc > 1)
 		die (_("unrecognized argument: %s"), argv[1]);
 
