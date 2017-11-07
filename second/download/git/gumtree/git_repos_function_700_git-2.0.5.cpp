static const char *wt_status_unmerged_status_string(int stagemask)
{
	switch (stagemask) {
	case 1:
		return _("both deleted:");
	case 2:
		return _("added by us:");
	case 3:
		return _("deleted by them:");
	case 4:
		return _("added by them:");
	case 5:
		return _("deleted by us:");
	case 6:
		return _("both added:");
	case 7:
		return _("both modified:");
	default:
		die(_("bug: unhandled unmerged status %x"), stagemask);
	}
}