 		printf("%s%06o %s %d\t",
 		       tag,
 		       ce->ce_mode,
 		       find_unique_abbrev(ce->sha1,abbrev),
 		       ce_stage(ce));
 	}
+	write_eolinfo(ce, ce->name);
 	write_name(ce->name);
 	if (debug_mode) {
 		const struct stat_data *sd = &ce->ce_stat_data;
 
 		printf("  ctime: %d:%d\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
 		printf("  mtime: %d:%d\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
