			continue;
		default:
			die("unexpected deflate failure: %d", status);
		}
	}
	git_deflate_end(&s);
	git_SHA1_Final(sha1, &c);

	if (sha1out)
		hashcpy(sha1out, sha1);

	e = insert_object(sha1);

	if (mark)
		insert_mark(mark, e);

	if (e->idx.offset) {
		duplicate_count_by_type[OBJ_BLOB]++;
		truncate_pack(&checkpoint);

	} else if (find_sha1_pack(sha1, packed_git)) {
		e->type = OBJ_BLOB;
		e->pack_id = MAX_PACK_ID;
		e->idx.offset = 1; /* just not zero! */
		duplicate_count_by_type[OBJ_BLOB]++;
		truncate_pack(&checkpoint);

