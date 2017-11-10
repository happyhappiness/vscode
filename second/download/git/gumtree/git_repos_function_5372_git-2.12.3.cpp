static const char *push_to_checkout(unsigned char *sha1,
				    struct argv_array *env,
				    const char *work_tree)
{
	argv_array_pushf(env, "GIT_WORK_TREE=%s", absolute_path(work_tree));
	if (run_hook_le(env->argv, push_to_checkout_hook,
			sha1_to_hex(sha1), NULL))
		return "push-to-checkout hook declined";
	else
		return NULL;
}