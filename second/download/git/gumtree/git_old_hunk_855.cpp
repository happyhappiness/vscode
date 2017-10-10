		printf_ln(_("To restore the original branch and stop patching, run \"%s --abort\"."), cmdline);
	}

	exit(128);
}

static void am_signoff(struct strbuf *sb)
{
	char *cp;
	struct strbuf mine = STRBUF_INIT;

	/* Does it end with our own sign-off? */
	strbuf_addf(&mine, "\n%s%s\n",
		    sign_off_header,
		    fmt_name(getenv("GIT_COMMITTER_NAME"),
			     getenv("GIT_COMMITTER_EMAIL")));
	if (mine.len < sb->len &&
	    !strcmp(mine.buf, sb->buf + sb->len - mine.len))
		goto exit; /* no need to duplicate */

	/* Does it have any Signed-off-by: in the text */
	for (cp = sb->buf;
	     cp && *cp && (cp = strstr(cp, sign_off_header)) != NULL;
	     cp = strchr(cp, '\n')) {
		if (sb->buf == cp || cp[-1] == '\n')
			break;
	}

	strbuf_addstr(sb, mine.buf + !!cp);
exit:
	strbuf_release(&mine);
}

/**
 * Appends signoff to the "msg" field of the am_state.
 */
static void am_append_signoff(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	strbuf_attach(&sb, state->msg, state->msg_len, state->msg_len);
	am_signoff(&sb);
	state->msg = strbuf_detach(&sb, &state->msg_len);
}

/**
 * Parses `mail` using git-mailinfo, extracting its patch and authorship info.
 * state->msg will be set to the patch message. state->author_name,
