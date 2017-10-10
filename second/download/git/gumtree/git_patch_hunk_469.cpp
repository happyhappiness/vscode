 			struct strbuf c = STRBUF_INIT;
 			if (multi_ack == 2)     strbuf_addstr(&c, " multi_ack_detailed");
 			if (multi_ack == 1)     strbuf_addstr(&c, " multi_ack");
 			if (no_done)            strbuf_addstr(&c, " no-done");
 			if (use_sideband == 2)  strbuf_addstr(&c, " side-band-64k");
 			if (use_sideband == 1)  strbuf_addstr(&c, " side-band");
+			if (args->deepen_relative) strbuf_addstr(&c, " deepen-relative");
 			if (args->use_thin_pack) strbuf_addstr(&c, " thin-pack");
 			if (args->no_progress)   strbuf_addstr(&c, " no-progress");
 			if (args->include_tag)   strbuf_addstr(&c, " include-tag");
 			if (prefer_ofs_delta)   strbuf_addstr(&c, " ofs-delta");
+			if (deepen_since_ok)    strbuf_addstr(&c, " deepen-since");
+			if (deepen_not_ok)      strbuf_addstr(&c, " deepen-not");
 			if (agent_supported)    strbuf_addf(&c, " agent=%s",
 							    git_user_agent_sanitized());
 			packet_buf_write(&req_buf, "want %s%s\n", remote_hex, c.buf);
 			strbuf_release(&c);
 		} else
 			packet_buf_write(&req_buf, "want %s\n", remote_hex);
