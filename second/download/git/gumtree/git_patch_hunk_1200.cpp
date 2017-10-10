 			fprintf(stderr, _("See \"git help gc\" for manual housekeeping.\n"));
 		}
 		if (detach_auto) {
 			if (report_last_gc_error())
 				return -1;
 
+			if (lock_repo_for_gc(force, &pid))
+				return 0;
 			if (gc_before_repack())
 				return -1;
+			delete_tempfile(&pidfile);
+
 			/*
 			 * failure to daemonize is ok, we'll continue
 			 * in foreground
 			 */
 			daemonized = !daemonize();
 		}
