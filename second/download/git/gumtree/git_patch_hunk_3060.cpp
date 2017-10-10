 				printf_ln(rebasing ?
 					  _("Branch %s set up to track local ref %s by rebasing.") :
 					  _("Branch %s set up to track local ref %s."),
 					  local, remote);
 		}
 	}
+
+	return 0;
+
+out_err:
+	strbuf_release(&key);
+	error(_("Unable to write upstream branch configuration"));
+
+	advise(_(tracking_advice),
+	       origin ? origin : "",
+	       origin ? "/" : "",
+	       shortname ? shortname : remote);
+
+	return -1;
 }
 
 /*
  * This is called when new_ref is branched off of orig_ref, and tries
  * to infer the settings for branch.<new_ref>.{remote,merge} from the
  * config.
  */
-static int setup_tracking(const char *new_ref, const char *orig_ref,
-			  enum branch_track track, int quiet)
+static void setup_tracking(const char *new_ref, const char *orig_ref,
+			   enum branch_track track, int quiet)
 {
 	struct tracking tracking;
 	int config_flags = quiet ? 0 : BRANCH_CONFIG_VERBOSE;
 
 	memset(&tracking, 0, sizeof(tracking));
 	tracking.spec.dst = (char *)orig_ref;
 	if (for_each_remote(find_tracked_branch, &tracking))
-		return 1;
+		return;
 
 	if (!tracking.matches)
 		switch (track) {
 		case BRANCH_TRACK_ALWAYS:
 		case BRANCH_TRACK_EXPLICIT:
 		case BRANCH_TRACK_OVERRIDE:
 			break;
 		default:
-			return 1;
+			return;
 		}
 
 	if (tracking.matches > 1)
-		return error(_("Not tracking: ambiguous information for ref %s"),
-				orig_ref);
+		die(_("Not tracking: ambiguous information for ref %s"),
+		    orig_ref);
 
-	install_branch_config(config_flags, new_ref, tracking.remote,
-			      tracking.src ? tracking.src : orig_ref);
+	if (install_branch_config(config_flags, new_ref, tracking.remote,
+			      tracking.src ? tracking.src : orig_ref) < 0)
+		exit(-1);
 
 	free(tracking.src);
-	return 0;
 }
 
 int read_branch_desc(struct strbuf *buf, const char *branch_name)
 {
 	char *v = NULL;
 	struct strbuf name = STRBUF_INIT;
