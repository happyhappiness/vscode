		case DENY_UNCONFIGURED:
			rp_error("refusing to update checked out branch: %s", name);
			if (deny_current_branch == DENY_UNCONFIGURED)
				refuse_unconfigured_deny();
			return "branch is currently checked out";
		case DENY_UPDATE_INSTEAD:
			ret = update_worktree(new_sha1);
			if (ret)
				return ret;
			break;
		}
	}

	if (!is_null_sha1(new_sha1) && !has_sha1_file(new_sha1)) {
		error("unpack should have generated %s, "
		      "but I can't find it!", sha1_to_hex(new_sha1));
		return "bad pack";
	}

	if (!is_null_sha1(old_sha1) && is_null_sha1(new_sha1)) {
		if (deny_deletes && starts_with(name, "refs/heads/")) {
			rp_error("denying ref deletion for %s", name);
			return "deletion prohibited";
		}

		if (head_name && !strcmp(namespaced_name, head_name)) {
