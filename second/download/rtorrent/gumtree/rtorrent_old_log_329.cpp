print_buffer(first, last, " [H %u/%u]",
                       control->core()->get_poll_manager()->get_http_stack()->active(),
                       control->core()->get_poll_manager()->get_http_stack()->max_active());