			continue;
		if (diter->basename[0] == '.')
			continue;
		if (ends_with(diter->basename, ".lock"))
			continue;

		if (refs_read_ref_full(iter->ref_store,
				       diter->relative_path, 0,
				       iter->oid.hash, &flags)) {
			error("bad ref for %s", diter->path.buf);
			continue;
		}

		iter->base.refname = diter->relative_path;
		iter->base.oid = &iter->oid;
