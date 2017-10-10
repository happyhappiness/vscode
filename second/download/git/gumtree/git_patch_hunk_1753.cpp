 				fix_thin = 0;
 				continue;
 			}
 
 			usage(receive_pack_usage);
 		}
-		if (dir)
+		if (service_dir)
 			usage(receive_pack_usage);
-		dir = arg;
+		service_dir = arg;
 	}
-	if (!dir)
+	if (!service_dir)
 		usage(receive_pack_usage);
 
 	setup_path();
 
-	if (!enter_repo(dir, 0))
-		die("'%s' does not appear to be a git repository", dir);
+	if (!enter_repo(service_dir, 0))
+		die("'%s' does not appear to be a git repository", service_dir);
 
 	git_config(receive_pack_config, NULL);
+	if (cert_nonce_seed)
+		push_cert_nonce = prepare_push_cert_nonce(service_dir, time(NULL));
 
 	if (0 <= transfer_unpack_limit)
 		unpack_limit = transfer_unpack_limit;
 	else if (0 <= receive_unpack_limit)
 		unpack_limit = receive_unpack_limit;
 
