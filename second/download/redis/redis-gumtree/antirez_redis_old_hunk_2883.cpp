        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Clients\r\n"
            "connected_clients:%d\r\n"
            "client_longest_output_list:%lu\r\n"
            "client_biggest_input_buf:%lu\r\n"
            "blocked_clients:%d\r\n",
