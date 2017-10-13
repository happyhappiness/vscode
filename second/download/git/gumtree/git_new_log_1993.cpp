strbuf_addf(err, "unable to resolve reference %s: %s",
				    orig_refname, strerror(last_errno));