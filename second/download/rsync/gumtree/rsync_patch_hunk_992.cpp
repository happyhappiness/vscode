 				    "Invalid argument passed to --chmod (%s)\n",
 				    arg);
 				return 0;
 			}
 			break;
 
+		case OPT_INFO:
+			arg = poptGetOptArg(pc);
+			parse_output_words(info_words, info_levels, arg, USER_PRIORITY);
+			break;
+
+		case OPT_DEBUG:
+			arg = poptGetOptArg(pc);
+			parse_output_words(debug_words, debug_levels, arg, USER_PRIORITY);
+			break;
+
+		case OPT_USERMAP:
+			if (usermap) {
+				if (usermap_via_chown) {
+					snprintf(err_buf, sizeof err_buf,
+					    "--usermap conflicts with prior --chown.\n");
+					return 0;
+				}
+				snprintf(err_buf, sizeof err_buf,
+				    "You can only specify --usermap once.\n");
+				return 0;
+			}
+			usermap = (char *)poptGetOptArg(pc);
+			usermap_via_chown = False;
+			break;
+
+		case OPT_GROUPMAP:
+			if (groupmap) {
+				if (groupmap_via_chown) {
+					snprintf(err_buf, sizeof err_buf,
+					    "--groupmap conflicts with prior --chown.\n");
+					return 0;
+				}
+				snprintf(err_buf, sizeof err_buf,
+				    "You can only specify --groupmap once.\n");
+				return 0;
+			}
+			groupmap = (char *)poptGetOptArg(pc);
+			groupmap_via_chown = False;
+			break;
+
+		case OPT_CHOWN: {
+			const char *chown = poptGetOptArg(pc);
+			int len;
+			if ((arg = strchr(chown, ':')) != NULL)
+				len = arg++ - chown;
+			else
+				len = strlen(chown);
+			if (len) {
+				if (usermap) {
+					if (!usermap_via_chown) {
+						snprintf(err_buf, sizeof err_buf,
+						    "--chown conflicts with prior --usermap.\n");
+						return 0;
+					}
+					snprintf(err_buf, sizeof err_buf,
+					    "You can only specify a user-affecting --chown once.\n");
+					return 0;
+				}
+				if (asprintf(&usermap, "*:%.*s", len, chown) < 0)
+					out_of_memory("parse_arguments");
+				usermap_via_chown = True;
+			}
+			if (arg && *arg) {
+				if (groupmap) {
+					if (!groupmap_via_chown) {
+						snprintf(err_buf, sizeof err_buf,
+						    "--chown conflicts with prior --groupmap.\n");
+						return 0;
+					}
+					snprintf(err_buf, sizeof err_buf,
+					    "You can only specify a group-affecting --chown once.\n");
+					return 0;
+				}
+				if (asprintf(&groupmap, "*:%s", arg) < 0)
+					out_of_memory("parse_arguments");
+				groupmap_via_chown = True;
+			}
+			break;
+		}
+
 		case OPT_HELP:
 			usage(FINFO);
 			exit_cleanup(0);
 
 		case 'A':
 #ifdef SUPPORT_ACLS
