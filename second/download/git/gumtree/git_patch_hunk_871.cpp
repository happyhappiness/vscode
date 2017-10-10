 				qname = quote_path_relative(item->string, NULL, &buf);
 				printf(dry_run ? _(msg_would_remove) : _(msg_remove), qname);
 			}
 		} else {
 			res = dry_run ? 0 : unlink(abs_path.buf);
 			if (res) {
+				int saved_errno = errno;
 				qname = quote_path_relative(item->string, NULL, &buf);
-				warning(_(msg_warn_remove_failed), qname);
+				errno = saved_errno;
+				warning_errno(_(msg_warn_remove_failed), qname);
 				errors++;
 			} else if (!quiet) {
 				qname = quote_path_relative(item->string, NULL, &buf);
 				printf(dry_run ? _(msg_would_remove) : _(msg_remove), qname);
 			}
 		}
