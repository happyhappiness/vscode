 			write_in_full(1, buf, payload_size);
 		return error("no signature found");
 	}
 
 	ret = check_signature(buf, payload_size, buf + payload_size,
 				size - payload_size, &sigc);
-	print_signature_buffer(&sigc, flags);
+
+	if (!(flags & GPG_VERIFY_OMIT_STATUS))
+		print_signature_buffer(&sigc, flags);
 
 	signature_check_clear(&sigc);
 	return ret;
 }
 
 int gpg_verify_tag(const unsigned char *sha1, const char *name_to_report,
