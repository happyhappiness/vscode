
    if ((stat(SUEXEC_BIN, &wrapper)) != 0)
	return (ap_suexec_enabled);

    if ((wrapper.st_mode & S_ISUID) && wrapper.st_uid == 0) {
	ap_suexec_enabled = 1;
    }
#endif /* ndef WIN32 */
    return (ap_suexec_enabled);
}

/*****************************************************************
