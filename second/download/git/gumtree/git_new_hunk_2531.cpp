
	if (!branch_name)
		branch_name = find_branch_name(rev);

	msg = body;
	pp.fmt = CMIT_FMT_EMAIL;
	pp.date_mode.type = DATE_RFC2822;
	pp_user_info(&pp, NULL, &sb, committer, encoding);
	pp_title_line(&pp, &msg, &sb, encoding, need_8bit_cte);
	pp_remainder(&pp, &msg, &sb, 0);
	add_branch_description(&sb, branch_name);
	printf("%s\n", sb.buf);

