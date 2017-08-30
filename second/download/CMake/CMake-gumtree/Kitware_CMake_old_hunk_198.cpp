#if !HAVE_LINK
		return (EPERM);
#else
		r = link(linkname, a->name) ? errno : 0;
		/*
		 * New cpio and pax formats allow hardlink entries
