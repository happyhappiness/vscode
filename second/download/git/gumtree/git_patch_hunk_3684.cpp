 	if (opt_gpg_sign)
 		argv_array_push(&args, opt_gpg_sign);
 	if (opt_autostash == 0)
 		argv_array_push(&args, "--no-autostash");
 	else if (opt_autostash == 1)
 		argv_array_push(&args, "--autostash");
+	if (opt_verify_signatures &&
+	    !strcmp(opt_verify_signatures, "--verify-signatures"))
+		warning(_("ignoring --verify-signatures for rebase"));
 
 	argv_array_push(&args, "--onto");
 	argv_array_push(&args, sha1_to_hex(merge_head));
 
 	if (fork_point && !is_null_sha1(fork_point))
 		argv_array_push(&args, sha1_to_hex(fork_point));
