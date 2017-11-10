static int show_push_info_item(struct string_list_item *item, void *cb_data)
{
	struct show_info *show_info = cb_data;
	struct push_info *push_info = item->util;
	const char *src = item->string, *status = NULL;

	switch (push_info->status) {
	case PUSH_STATUS_CREATE:
		status = _("create");
		break;
	case PUSH_STATUS_DELETE:
		status = _("delete");
		src = _("(none)");
		break;
	case PUSH_STATUS_UPTODATE:
		status = _("up to date");
		break;
	case PUSH_STATUS_FASTFORWARD:
		status = _("fast-forwardable");
		break;
	case PUSH_STATUS_OUTOFDATE:
		status = _("local out of date");
		break;
	case PUSH_STATUS_NOTQUERIED:
		break;
	}
	if (status) {
		if (push_info->forced)
			printf_ln(_("    %-*s forces to %-*s (%s)"), show_info->width, src,
			       show_info->width2, push_info->dest, status);
		else
			printf_ln(_("    %-*s pushes to %-*s (%s)"), show_info->width, src,
			       show_info->width2, push_info->dest, status);
	} else {
		if (push_info->forced)
			printf_ln(_("    %-*s forces to %s"), show_info->width, src,
			       push_info->dest);
		else
			printf_ln(_("    %-*s pushes to %s"), show_info->width, src,
			       push_info->dest);
	}
	return 0;
}