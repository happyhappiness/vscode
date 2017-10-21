			 * we need to remember that we're using a
			 * non-default setting. */
			modify_window_set = 1;
			break;

		case OPT_FILTER:
			parse_filter_str(&filter_list, poptGetOptArg(pc),
					rule_template(0), 0);
			break;

		case OPT_EXCLUDE:
			parse_filter_str(&filter_list, poptGetOptArg(pc),
					rule_template(0), XFLG_OLD_PREFIXES);
			break;

		case OPT_INCLUDE:
			parse_filter_str(&filter_list, poptGetOptArg(pc),
					rule_template(FILTRULE_INCLUDE), XFLG_OLD_PREFIXES);
			break;

		case OPT_EXCLUDE_FROM:
		case OPT_INCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = sanitize_path(NULL, arg, NULL, 0, SP_DEFAULT);
			if (daemon_filter_list.head) {
				int rej;
				char *cp = strdup(arg);
				if (!cp)
					out_of_memory("parse_arguments");
				if (!*cp)
					rej = 1;
				else {
					char *dir = cp + (*cp == '/' ? module_dirlen : 0);
					clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
					rej = check_filter(&daemon_filter_list, FLOG, dir, 0) < 0;
				}
				free(cp);
				if (rej)
					goto options_rejected;
			}
			parse_filter_file(&filter_list, arg,
				rule_template(opt == OPT_INCLUDE_FROM ? FILTRULE_INCLUDE : 0),
				XFLG_FATAL_ERRORS | XFLG_OLD_PREFIXES);
			break;

		case 'a':
			if (refused_archive_part) {
				create_refuse_error(refused_archive_part);
