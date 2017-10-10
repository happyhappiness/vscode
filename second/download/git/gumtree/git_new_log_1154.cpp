(use_push_options) {
		struct string_list_item *item;

		packet_buf_flush(&req_buf);
		for_each_string_list_item(item, args->push_options)
			packet_buf_write(&req_buf, "%s", item->string);
	};