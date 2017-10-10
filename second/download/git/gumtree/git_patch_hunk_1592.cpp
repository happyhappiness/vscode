 			continue;
 		wt_longstatus_print_change_data(s, WT_STATUS_CHANGED, it);
 	}
 	wt_longstatus_print_trailer(s);
 }
 
+static int stash_count_refs(struct object_id *ooid, struct object_id *noid,
+			    const char *email, timestamp_t timestamp, int tz,
+			    const char *message, void *cb_data)
+{
+	int *c = cb_data;
+	(*c)++;
+	return 0;
+}
+
+static void wt_longstatus_print_stash_summary(struct wt_status *s)
+{
+	int stash_count = 0;
+
+	for_each_reflog_ent("refs/stash", stash_count_refs, &stash_count);
+	if (stash_count > 0)
+		status_printf_ln(s, GIT_COLOR_NORMAL,
+				 Q_("Your stash currently has %d entry",
+				    "Your stash currently has %d entries", stash_count),
+				 stash_count);
+}
+
 static void wt_longstatus_print_submodule_summary(struct wt_status *s, int uncommitted)
 {
 	struct child_process sm_summary = CHILD_PROCESS_INIT;
 	struct strbuf cmd_stdout = STRBUF_INIT;
 	struct strbuf summary = STRBUF_INIT;
 	char *summary_content;
