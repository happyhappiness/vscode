strbuf_addf(err, _("Expected git repo version <= %d, found %d"),
			    GIT_REPO_VERSION_READ, format->version);