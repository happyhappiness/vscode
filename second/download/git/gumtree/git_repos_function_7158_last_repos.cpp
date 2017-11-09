int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;

	struct credential_operation const *try_op = credential_helper_ops;
	struct credential cred = CREDENTIAL_INIT;

	if (!argv[1]) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	g_set_application_name("Git Credential Helper");

	/* lookup operation callback */
	while (try_op->name && strcmp(argv[1], try_op->name))
		try_op++;

	/* unsupported operation given -- ignore silently */
	if (!try_op->name || !try_op->op)
		goto out;

	ret = credential_read(&cred);
	if (ret)
		goto out;

	/* perform credential operation */
	ret = (*try_op->op)(&cred);

	credential_write(&cred);

out:
	credential_clear(&cred);
	return ret;
}