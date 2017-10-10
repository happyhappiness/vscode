	strbuf_release(&str);
	fclose(fp);

	return res;
}

static int bisect_checkout(const unsigned char *bisect_rev, int no_checkout)
{
	char bisect_rev_hex[GIT_SHA1_HEXSZ + 1];

	memcpy(bisect_rev_hex, sha1_to_hex(bisect_rev), GIT_SHA1_HEXSZ + 1);
	update_ref(NULL, "BISECT_EXPECTED_REV", bisect_rev, NULL, 0, UPDATE_REFS_DIE_ON_ERR);

	argv_checkout[2] = bisect_rev_hex;
	if (no_checkout) {
		update_ref(NULL, "BISECT_HEAD", bisect_rev, NULL, 0, UPDATE_REFS_DIE_ON_ERR);
	} else {
		int res;
		res = run_command_v_opt(argv_checkout, RUN_GIT_CMD);
		if (res)
			exit(res);
	}
