 		xdemitconf_t xecfg;
 
 		memset(&xpp, 0, sizeof(xpp));
 		memset(&xecfg, 0, sizeof(xecfg));
 		xecfg.ctxlen = 1; /* at least one context line */
 		xpp.flags = 0;
-		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
-				  &xpp, &xecfg))
-			die("unable to generate checkdiff for %s", one->path);
+		xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
+			      &xpp, &xecfg);
 
 		if (data.ws_rule & WS_BLANK_AT_EOF) {
 			struct emit_callback ecbdata;
 			int blank_at_eof;
 
 			ecbdata.ws_rule = data.ws_rule;
