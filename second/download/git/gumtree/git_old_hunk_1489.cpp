		if (!pack_sig_ofs)
			pack_sig_ofs = p->pack_size - 20;
		if (offset > pack_sig_ofs)
			remaining -= (unsigned int)(offset - pack_sig_ofs);
		git_SHA1_Update(&ctx, in, remaining);
	} while (offset < pack_sig_ofs);
	git_SHA1_Final(sha1, &ctx);
	pack_sig = use_pack(p, w_curs, pack_sig_ofs, NULL);
	if (hashcmp(sha1, pack_sig))
		err = error("%s SHA1 checksum mismatch",
			    p->pack_name);
	if (hashcmp(index_base + index_size - 40, pack_sig))
		err = error("%s SHA1 does not match its index",
			    p->pack_name);
	unuse_pack(w_curs);
