 	if (strcmp(cmd, "create") && (bundle_fd =
 				read_bundle_header(bundle_file, &header)) < 0)
 		return 1;
 
 	if (!strcmp(cmd, "verify")) {
 		close(bundle_fd);
+		if (argc != 1) {
+			usage(builtin_bundle_usage);
+			return 1;
+		}
 		if (verify_bundle(&header, 1))
 			return 1;
 		fprintf(stderr, _("%s is okay\n"), bundle_file);
 		return 0;
 	}
 	if (!strcmp(cmd, "list-heads")) {
 		close(bundle_fd);
 		return !!list_bundle_refs(&header, argc, argv);
 	}
 	if (!strcmp(cmd, "create")) {
+		if (argc < 2) {
+			usage(builtin_bundle_usage);
+			return 1;
+		}
 		if (!startup_info->have_repository)
 			die(_("Need a repository to create a bundle."));
 		return !!create_bundle(&header, bundle_file, argc, argv);
 	} else if (!strcmp(cmd, "unbundle")) {
 		if (!startup_info->have_repository)
 			die(_("Need a repository to unbundle."));
