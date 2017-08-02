snprintf(
			std_uuid, sizeof(std_uuid),
			"<urn:uuid:%08x-%04x-%04x-%04x-%04x%08x>",
			u.u[0U],
			u.u[1U] >> 16U, u.u[1U] & 0xffffU,
			u.u[2U] >> 16U, u.u[2U] & 0xffffU,
			u.u[3U])