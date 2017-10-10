		printf("in-pack: %lu\n", packed);
		printf("packs: %lu\n", num_pack);
		printf("size-pack: %s\n", pack_buf.buf);
		printf("prune-packable: %lu\n", packed_loose);
		printf("garbage: %lu\n", garbage);
		printf("size-garbage: %s\n", garbage_buf.buf);
		strbuf_release(&loose_buf);
		strbuf_release(&pack_buf);
		strbuf_release(&garbage_buf);
	} else {
		struct strbuf buf = STRBUF_INIT;
		if (human_readable)
