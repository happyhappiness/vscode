		die("you must specify exactly one commit to test");

	fprintf(stderr, "Bitmap v%d test (%d entries loaded)\n",
		bitmap_git.version, bitmap_git.entry_count);

	root = revs->pending.objects[0].item;
	pos = kh_get_sha1(bitmap_git.bitmaps, root->oid.hash);

	if (pos < kh_end(bitmap_git.bitmaps)) {
		struct stored_bitmap *st = kh_value(bitmap_git.bitmaps, pos);
		struct ewah_bitmap *bm = lookup_stored_bitmap(st);

		fprintf(stderr, "Found bitmap for %s. %d bits / %08x checksum\n",
			oid_to_hex(&root->oid), (int)bm->bit_size, ewah_checksum(bm));

		result = ewah_to_bitmap(bm);
	}

	if (result == NULL)
		die("Commit %s doesn't have an indexed bitmap", oid_to_hex(&root->oid));

	revs->tag_objects = 1;
	revs->tree_objects = 1;
	revs->blob_objects = 1;

	result_popcnt = bitmap_popcount(result);
