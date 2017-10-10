		/* FALLTHROUGH */
	case 1:
		upstream = argv[0];
		break;
	default:
		current_branch = branch_get(NULL);
		upstream = branch_get_upstream(current_branch, NULL);
		if (!upstream) {
			fprintf(stderr, _("Could not find a tracked"
					" remote branch, please"
					" specify <upstream> manually.\n"));
			usage_with_options(cherry_usage, options);
		}
	}

	init_revisions(&revs, prefix);
	revs.max_parents = 1;

	if (add_pending_commit(head, &revs, 0))
