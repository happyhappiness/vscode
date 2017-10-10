			error("failed to apply delta");

		free(delta_data);
		free(external_base);
	}

	if (final_type)
		*final_type = type;
	if (final_size)
		*final_size = size;

	unuse_pack(&w_curs);

	if (delta_stack != small_delta_stack)
		free(delta_stack);

