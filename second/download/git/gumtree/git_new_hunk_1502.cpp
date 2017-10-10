			if (allow < 0)
				allow = git_env_bool("GIT_ALLOW_NULL_SHA1", 0);
			if (allow)
				warning(msg, ce->name);
			else
				return error(msg, ce->name);

			drop_cache_tree = 1;
		}
		if (ce_write_entry(&c, newfd, ce, previous_name) < 0)
			return -1;
	}
	strbuf_release(&previous_name_buf);

