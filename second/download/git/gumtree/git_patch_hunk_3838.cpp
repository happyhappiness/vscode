 		return _("deleted by us:");
 	case 6:
 		return _("both added:");
 	case 7:
 		return _("both modified:");
 	default:
-		die(_("bug: unhandled unmerged status %x"), stagemask);
+		die("BUG: unhandled unmerged status %x", stagemask);
 	}
 }
 
 static const char *wt_status_diff_status_string(int status)
 {
 	switch (status) {
