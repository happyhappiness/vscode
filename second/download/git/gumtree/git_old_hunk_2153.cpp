free_return:
	free(signing_key);
	strbuf_release(&cert);
	return update_seen;
}

int send_pack(struct send_pack_args *args,
	      int fd[], struct child_process *conn,
	      struct ref *remote_refs,
	      struct sha1_array *extra_have)
{
	int in = fd[0];
