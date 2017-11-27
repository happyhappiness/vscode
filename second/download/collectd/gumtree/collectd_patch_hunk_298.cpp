 
 	plugin_log (SvIV (ST (0)), "%s", SvPV_nolen (ST (1)));
 	XSRETURN_YES;
 } /* static XS (Collectd_plugin_log) */
 
 /*
+ * Collectd::_fc_register (type, name)
+ *
+ * type:
+ *   match | target
+ *
+ * name:
+ *   name of the match
+ */
+static XS (Collectd__fc_register)
+{
+	int   type;
+	char *name;
+
+	int ret = 0;
+
+	dXSARGS;
+
+	if (2 != items) {
+		log_err ("Usage: Collectd::_fc_register(type, name)");
+		XSRETURN_EMPTY;
+	}
+
+	type = SvIV (ST (0));
+	name = SvPV_nolen (ST (1));
+
+	if (FC_MATCH == type)
+		ret = fc_register_match (name, pmatch);
+	else if (FC_TARGET == type)
+		ret = fc_register_target (name, ptarget);
+
+	if (0 == ret)
+		XSRETURN_YES;
+	else
+		XSRETURN_EMPTY;
+} /* static XS (Collectd_fc_register) */
+
+/*
  * Collectd::call_by_name (...).
  *
  * Call a Perl sub identified by its name passed through $Collectd::cb_name.
  */
 static XS (Collectd_call_by_name)
 {
