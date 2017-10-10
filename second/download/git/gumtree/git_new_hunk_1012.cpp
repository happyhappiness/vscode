				return ACK_common;
			if (strstr(arg, "ready"))
				return ACK_ready;
			return ACK;
		}
	}
	if (skip_prefix(line, "ERR ", &arg))
		die(_("remote error: %s"), arg);
	die(_("git fetch-pack: expected ACK/NAK, got '%s'"), line);
}

static void send_request(struct fetch_pack_args *args,
			 int fd, struct strbuf *buf)
{
