 		ret += git_config_from_file(fn, repo_config, data);
 		found += 1;
 	}
 
 	switch (git_config_from_parameters(fn, data)) {
 	case -1: /* error */
-		die("unable to parse command-line config");
+		die(_("unable to parse command-line config"));
 		break;
 	case 0: /* found nothing */
 		break;
 	default: /* found at least one item */
 		found++;
 		break;
