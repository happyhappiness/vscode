			break;

		case OPT_EXCLUDE_FROM:
		case OPT_INCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = sanitize_path(NULL, arg, NULL, 0, SP_DEFAULT);
			if (daemon_filter_list.head) {
				int rej;
				char *dir, *cp = strdup(arg);
				if (!cp)
					out_of_memory("parse_arguments");
				if (!*cp)
					goto options_rejected;
				dir = cp + (*cp == '/' ? module_dirlen : 0);
				clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
				rej = check_filter(&daemon_filter_list, FLOG, dir, 0) < 0;
				free(cp);
				if (rej)
					goto options_rejected;
			}
			parse_filter_file(&filter_list, arg,
				opt == OPT_INCLUDE_FROM ? MATCHFLG_INCLUDE : 0,
