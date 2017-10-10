fprintf(stderr, "Found bitmap for %s. %d bits / %08x checksum\n",
			oid_to_hex(&root->oid), (int)bm->bit_size, ewah_checksum(bm));