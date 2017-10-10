			next = strchrnul(found, '\n');
			sigc->signer = xmemdupz(found, next - found);
		}
	}
}

/*
 * Look at GPG signed content (e.g. a signed tag object), whose
 * payload is followed by a detached signature on it.  Return the
 * offset where the embedded detached signature begins, or the end of
 * the data when there is no such signature.
 */
