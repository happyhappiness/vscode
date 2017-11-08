void signature_check_clear(struct signature_check *sigc)
{
	free(sigc->payload);
	free(sigc->gpg_output);
	free(sigc->gpg_status);
	free(sigc->signer);
	free(sigc->key);
	sigc->payload = NULL;
	sigc->gpg_output = NULL;
	sigc->gpg_status = NULL;
	sigc->signer = NULL;
	sigc->key = NULL;
}