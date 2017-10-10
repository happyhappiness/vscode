		} else
			warning(_("Not updating non-default fetch refspec\n"
				  "\t%s\n"
				  "\tPlease update the configuration manually if necessary."),
				buf2.buf);

		git_config_set_multivar(buf.buf, buf2.buf, "^$", 0);
	}

	read_branches();
	for (i = 0; i < branch_list.nr; i++) {
		struct string_list_item *item = branch_list.items + i;
		struct branch_info *info = item->util;
		if (info->remote_name && !strcmp(info->remote_name, rename.old)) {
			strbuf_reset(&buf);
			strbuf_addf(&buf, "branch.%s.remote", item->string);
			git_config_set(buf.buf, rename.new);
		}
	}

	if (!refspec_updated)
		return 0;

