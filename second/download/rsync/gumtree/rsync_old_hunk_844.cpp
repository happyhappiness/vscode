			break;

		case OPT_EXCLUDE_FROM:
		case OPT_INCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = sanitize_path(NULL, arg, NULL, 0);
			if (server_filter_list.head) {
				char *cp = (char *)arg;
				if (!*cp)
					goto options_rejected;
				clean_fname(cp, 1);
				if (check_filter(&server_filter_list, cp, 0) < 0)
					goto options_rejected;
			}
			parse_filter_file(&filter_list, arg,
				opt == OPT_INCLUDE_FROM ? MATCHFLG_INCLUDE : 0,
				XFLG_FATAL_ERRORS | XFLG_OLD_PREFIXES);
			break;

