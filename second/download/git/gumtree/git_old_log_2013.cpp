fprintf(stderr, "Found bitmap for %s. %d bits / %08x checksum\n",
			sha1_to_hex(root->sha1), (int)bm->bit_size, ewah_checksum(bm));