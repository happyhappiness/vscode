 	idx_tmp_name = write_idx_file(NULL, written_list, nr_written,
 				      pack_idx_opts, sha1);
 	if (adjust_shared_perm(idx_tmp_name))
 		die_errno("unable to make temporary index file readable");
 
 	strbuf_addf(name_buffer, "%s.pack", sha1_to_hex(sha1));
-	free_pack_by_name(name_buffer->buf);
 
 	if (rename(pack_tmp_name, name_buffer->buf))
 		die_errno("unable to rename temporary pack file");
 
 	strbuf_setlen(name_buffer, basename_len);
 
