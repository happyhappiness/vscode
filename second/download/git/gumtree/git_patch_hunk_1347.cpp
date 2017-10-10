 	FLEX_ALLOC_MEM(ent, pattern, pattern, len);
 	*reflog_expire_cfg_tail = ent;
 	reflog_expire_cfg_tail = &(ent->next);
 	return ent;
 }
 
-static int parse_expire_cfg_value(const char *var, const char *value, unsigned long *expire)
+static int parse_expire_cfg_value(const char *var, const char *value, timestamp_t *expire)
 {
 	if (!value)
 		return config_error_nonbool(var);
 	if (parse_expiry_date(value, expire))
 		return error(_("'%s' for '%s' is not a valid timestamp"),
 			     value, var);
