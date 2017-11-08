int reflog_expire(const char *refname, const unsigned char *sha1,
		  unsigned int flags,
		  reflog_expiry_prepare_fn prepare_fn,
		  reflog_expiry_should_prune_fn should_prune_fn,
		  reflog_expiry_cleanup_fn cleanup_fn,
		  void *policy_cb_data)
{
	return refs_reflog_expire(get_main_ref_store(),
				  refname, sha1, flags,
				  prepare_fn, should_prune_fn,
				  cleanup_fn, policy_cb_data);
}