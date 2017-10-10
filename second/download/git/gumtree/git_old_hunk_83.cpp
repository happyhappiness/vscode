					strbuf_addf(&value, "+%s:%s", our_head_points_at->name,
						our_head_points_at->name);
				else
					strbuf_addf(&value, "+%s:%s%s", our_head_points_at->name,
						branch_top->buf, option_branch);
			} else if (remote_head_points_at) {
				strbuf_addf(&value, "+%s:%s%s", remote_head_points_at->name,
						branch_top->buf,
						skip_prefix(remote_head_points_at->name, "refs/heads/"));
			}
			/*
			 * otherwise, the next "git fetch" will
			 * simply fetch from HEAD without updating
			 * any remote-tracking branch, which is what
			 * we want.
