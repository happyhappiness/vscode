			oid = &merge_remote_util(c)->obj->oid;
		} else {
			oid = &c->object.oid;
		}
		strbuf_addf(&buf, "%s\n", oid_to_hex(oid));
	}
	write_file_buf(git_path_merge_head(), buf.buf, buf.len);
	strbuf_addch(&merge_msg, '\n');
	write_file_buf(git_path_merge_msg(), merge_msg.buf, merge_msg.len);

	strbuf_reset(&buf);
	if (fast_forward == FF_NO)
		strbuf_addf(&buf, "no-ff");
	write_file_buf(git_path_merge_mode(), buf.buf, buf.len);
}

static int default_edit_option(void)
{
	static const char name[] = "GIT_MERGE_AUTOEDIT";
	const char *e = getenv(name);
