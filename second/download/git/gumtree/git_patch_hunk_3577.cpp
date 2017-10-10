 		keep_cr = 0;
 		git_config_get_bool("am.keepcr", &keep_cr);
 	}
 
 	switch (patch_format) {
 	case PATCH_FORMAT_MBOX:
-		return split_mail_mbox(state, paths, keep_cr);
+		return split_mail_mbox(state, paths, keep_cr, 0);
 	case PATCH_FORMAT_STGIT:
 		return split_mail_conv(stgit_patch_to_mail, state, paths, keep_cr);
 	case PATCH_FORMAT_STGIT_SERIES:
 		return split_mail_stgit_series(state, paths, keep_cr);
 	case PATCH_FORMAT_HG:
 		return split_mail_conv(hg_patch_to_mail, state, paths, keep_cr);
+	case PATCH_FORMAT_MBOXRD:
+		return split_mail_mbox(state, paths, keep_cr, 1);
 	default:
 		die("BUG: invalid patch_format");
 	}
 	return -1;
 }
 
