strbuf_addf(err, "unable to append to %s: %s",
				    logfile->buf, strerror(errno));