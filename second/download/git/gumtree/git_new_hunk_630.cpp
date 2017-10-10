
	die("BUG: unhandled push situation");
}

const char *branch_get_push(struct branch *branch, struct strbuf *err)
{
	if (!branch)
		return error_buf(err, _("HEAD does not point to a branch"));

	if (!branch->push_tracking_ref)
		branch->push_tracking_ref = branch_get_push_1(branch, err);
	return branch->push_tracking_ref;
}

static int ignore_symref_update(const char *refname)
