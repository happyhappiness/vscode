			continue;
		wt_longstatus_print_change_data(s, WT_STATUS_CHANGED, it);
	}
	wt_longstatus_print_trailer(s);
}

static void wt_longstatus_print_submodule_summary(struct wt_status *s, int uncommitted)
{
	struct child_process sm_summary = CHILD_PROCESS_INIT;
	struct strbuf cmd_stdout = STRBUF_INIT;
	struct strbuf summary = STRBUF_INIT;
	char *summary_content;
