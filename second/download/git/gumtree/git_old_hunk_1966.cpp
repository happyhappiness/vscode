				die("Not a valid object name %s", argv[i]);
			assert_sha1_type(sha1, OBJ_COMMIT);
			new_parent(lookup_commit(sha1), &parents);
			continue;
		}

		if (!memcmp(arg, "-S", 2)) {
			sign_commit = arg + 2;
			continue;
		}

		if (!strcmp(arg, "--no-gpg-sign")) {
			sign_commit = NULL;
			continue;
		}

