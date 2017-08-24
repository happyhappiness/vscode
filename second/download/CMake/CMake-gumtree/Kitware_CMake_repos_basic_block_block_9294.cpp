(a->format && a->format->has_encrypted_entries) {
		return (a->format->has_encrypted_entries)(a);
	}