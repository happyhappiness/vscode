			struct strbuf sb = STRBUF_INIT;
			if (!shown_url) {
				fprintf(stderr, _("From %.*s\n"), url_len, url);
				shown_url = 1;
			}
			format_display(&sb, '-', _("[deleted]"), NULL,
				       _("(none)"), prettify_refname(ref->name));
			fprintf(stderr, " %s\n",sb.buf);
			strbuf_release(&sb);
			warn_dangling_symref(stderr, dangling_msg, ref->name);
		}
	}

