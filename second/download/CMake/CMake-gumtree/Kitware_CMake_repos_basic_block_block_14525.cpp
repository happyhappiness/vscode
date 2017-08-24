{
		free(data->in_buffer_allocated);
		data->in_buffer_size = data->block_size;
		data->in_buffer_allocated =
		    malloc(data->in_buffer_size + pre_block_size);
		data->in_buffer = data->in_buffer_allocated + pre_block_size;
		if (!data->block_independence && data->compression_level >= 3)
		    data->in_buffer = data->in_buffer_allocated;
		data->in = data->in_buffer;
		data->in_buffer_size = data->block_size;
	}