 		packet_write(1, "%s %s\n", sha1_to_hex(sha1), path);
 	} else {
 		struct strbuf cap = STRBUF_INIT;
 
 		strbuf_addstr(&cap,
 			      "report-status delete-refs side-band-64k quiet");
+		if (advertise_atomic_push)
+			strbuf_addstr(&cap, " atomic");
 		if (prefer_ofs_delta)
 			strbuf_addstr(&cap, " ofs-delta");
 		if (push_cert_nonce)
 			strbuf_addf(&cap, " push-cert=%s", push_cert_nonce);
 		strbuf_addf(&cap, " agent=%s", git_user_agent_sanitized());
 		packet_write(1, "%s %s%c%s\n",
