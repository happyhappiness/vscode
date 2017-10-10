		} else if (0 <= sha1_array_lookup(&good_revs, mb)) {
			continue;
		} else if (0 <= sha1_array_lookup(&skipped_revs, mb)) {
			handle_skipped_merge_base(mb);
		} else {
			printf("Bisecting: a merge base must be tested\n");
			exit(bisect_checkout(sha1_to_hex(mb), no_checkout));
		}
	}

	free(rev);
	free_commit_list(result);
}
