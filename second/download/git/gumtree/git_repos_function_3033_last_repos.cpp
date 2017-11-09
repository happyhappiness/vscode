static timestamp_t check_expirations(void)
{
	static timestamp_t wait_for_entry_until;
	int i = 0;
	timestamp_t now = time(NULL);
	timestamp_t next = TIME_MAX;

	/*
	 * Initially give the client 30 seconds to actually contact us
	 * and store a credential before we decide there's no point in
	 * keeping the daemon around.
	 */
	if (!wait_for_entry_until)
		wait_for_entry_until = now + 30;

	while (i < entries_nr) {
		if (entries[i].expiration <= now) {
			entries_nr--;
			credential_clear(&entries[i].item);
			if (i != entries_nr)
				memcpy(&entries[i], &entries[entries_nr], sizeof(*entries));
			/*
			 * Stick around 30 seconds in case a new credential
			 * shows up (e.g., because we just removed a failed
			 * one, and we will soon get the correct one).
			 */
			wait_for_entry_until = now + 30;
		}
		else {
			if (entries[i].expiration < next)
				next = entries[i].expiration;
			i++;
		}
	}

	if (!entries_nr) {
		if (wait_for_entry_until <= now)
			return 0;
		next = wait_for_entry_until;
	}

	return next - now;
}