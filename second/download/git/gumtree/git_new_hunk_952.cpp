		case DENY_UNCONFIGURED:
			rp_error("refusing to update checked out branch: %s", name);
			if (deny_current_branch == DENY_UNCONFIGURED)
				refuse_unconfigured_deny();
			return "branch is currently checked out";
		case DENY_UPDATE_INSTEAD:
			ret = update_worktree(new_oid->hash);
			if (ret)
				return ret;
			break;
		}
	}

	if (!is_null_oid(new_oid) && !has_object_file(new_oid)) {
		error("unpack should have generated %s, "
		      "but I can't find it!", oid_to_hex(new_oid));
		return "bad pack";
	}

	if (!is_null_oid(old_oid) && is_null_oid(new_oid)) {
		if (deny_deletes && starts_with(name, "refs/heads/")) {
			rp_error("denying ref deletion for %s", name);
			return "deletion prohibited";
		}

		if (head_name && !strcmp(namespaced_name, head_name)) {
