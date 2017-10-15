print_buffer(first, last, " [H %u/%u]",
                       control->core()->http_stack()->active(),
                       control->core()->http_stack()->max_active());