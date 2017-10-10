		 * the object.
		 */
		if (!data)
			error("failed to apply delta");

		free(delta_data);
	}

	*final_type = type;
	*final_size = size;

	unuse_pack(&w_curs);
