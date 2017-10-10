
		if (get_sha1(argv[1], second_sha1))
			return NULL;
		second_token = lookup_commit_reference_gently(second_sha1, 0);
		if (!second_token)
			die(_("'%s' is not a commit"), argv[1]);
		if (hashcmp(second_token->object.sha1, head))
			return NULL;
	}
	return second_token;
}

static int evaluate_result(void)
