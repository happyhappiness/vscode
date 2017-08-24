{
		p = (unsigned char *)wnp->isoent->identifier;
		/* Extend the filename; foo.c --> foo___.c */
		memmove(p + wnp->noff + numsize, p + wnp_ext_off,
		    wnp->isoent->ext_len + nullsize);
		wnp->isoent->ext_off = wnp_ext_off = wnp->noff + numsize;
		wnp->isoent->id_len = wnp_ext_off + wnp->isoent->ext_len;
	}