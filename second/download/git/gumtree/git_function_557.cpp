void wt_status_print(struct wt_status *s)
{
	switch (s->status_format) {
	case STATUS_FORMAT_SHORT:
		wt_shortstatus_print(s);
		break;
	case STATUS_FORMAT_PORCELAIN:
		wt_porcelain_print(s);
		break;
	case STATUS_FORMAT_PORCELAIN_V2:
		wt_porcelain_v2_print(s);
		break;
	case STATUS_FORMAT_UNSPECIFIED:
		die("BUG: finalize_deferred_config() should have been called");
		break;
	case STATUS_FORMAT_NONE:
	case STATUS_FORMAT_LONG:
		wt_longstatus_print(s);
		break;
	}
}