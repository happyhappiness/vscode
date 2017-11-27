 
 	if (2 != items) {
 		log_err ("Usage: Collectd::plugin_log(level, message)");
 		XSRETURN_EMPTY;
 	}
 
-	plugin_log (SvIV (ST (0)), SvPV_nolen (ST (1)));
+	plugin_log (SvIV (ST (0)), "%s", SvPV_nolen (ST (1)));
 	XSRETURN_YES;
 } /* static XS (Collectd_plugin_log) */
 
 /*
  * Collectd::call_by_name (...).
  *
