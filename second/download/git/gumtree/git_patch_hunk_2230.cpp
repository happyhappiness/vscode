 		/* FALLTHROUGH */
 	case 1:
 		upstream = argv[0];
 		break;
 	default:
 		current_branch = branch_get(NULL);
-		if (!current_branch || !current_branch->merge
-					|| !current_branch->merge[0]
-					|| !current_branch->merge[0]->dst) {
+		upstream = branch_get_upstream(current_branch, NULL);
+		if (!upstream) {
 			fprintf(stderr, _("Could not find a tracked"
 					" remote branch, please"
 					" specify <upstream> manually.\n"));
 			usage_with_options(cherry_usage, options);
 		}
-
-		upstream = current_branch->merge[0]->dst;
 	}
 
 	init_revisions(&revs, prefix);
 	revs.max_parents = 1;
 
 	if (add_pending_commit(head, &revs, 0))
