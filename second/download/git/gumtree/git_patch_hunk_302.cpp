 			const char *slash = strchr(dir, '/');
 			if (!slash)
 				slash = dir + restlen;
 			namlen = slash - dir;
 			restlen -= namlen;
 			loginfo("userpath <%s>, request <%s>, namlen %d, restlen %d, slash <%s>", user_path, dir, namlen, restlen, slash);
-			snprintf(rpath, PATH_MAX, "%.*s/%s%.*s",
-				 namlen, dir, user_path, restlen, slash);
+			rlen = snprintf(rpath, sizeof(rpath), "%.*s/%s%.*s",
+					namlen, dir, user_path, restlen, slash);
+			if (rlen >= sizeof(rpath)) {
+				logerror("user-path too large: %s", rpath);
+				return NULL;
+			}
 			dir = rpath;
 		}
 	}
 	else if (interpolated_path && hi->saw_extended_args) {
 		struct strbuf expanded_path = STRBUF_INIT;
 		struct expand_path_context context;
