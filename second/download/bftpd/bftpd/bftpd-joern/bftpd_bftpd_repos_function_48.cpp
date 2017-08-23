int checkpass_pam(char *password)
{
	struct pam_conv conv = { conv_func, password };
	int retval = pam_start("bftpd", user, (struct pam_conv *) &conv,
						   (pam_handle_t **) & pamh);
	if (retval != PAM_SUCCESS) {
		printf("Error while initializing PAM: %s\n",
			   pam_strerror(pamh, retval));
		return 1;
	}
        /* 
        Allow Bftpd to build with OpenPAM
	pam_fail_delay(pamh, 0);
        */
	retval = pam_authenticate(pamh, 0);
	if (retval == PAM_SUCCESS)
		retval = pam_acct_mgmt(pamh, 0);
	if (retval == PAM_SUCCESS)
		pam_open_session(pamh, 0);
	if (retval != PAM_SUCCESS)
		return 1;
	else
		return 0;
}