      if (key == server_info_key_version)
        out.version = val;
      else if (key == server_info_key_bgsave_in_progress)
        out.bgsave_in_progress = unsigned_number_from_string(val) == 1;
      else if (key == server_info_key_connected_clients)
        out.connected_clients = unsigned_number_from_string(val);
      else if (key == server_info_key_connected_slaves)
        out.connected_slaves = unsigned_number_from_string(val);
      else if (key == server_info_key_used_memory)
        out.used_memory = unsigned_number_from_string(val);
      else if (key == server_info_key_changes_since_last_save)
        out.changes_since_last_save = unsigned_number_from_string(val);
      else if (key == server_info_key_last_save_time)
        out.last_save_time = unsigned_number_from_string(val);
      else if (key == server_info_key_total_connections_received)
        out.total_connections_received = unsigned_number_from_string(val);
      else if (key == server_info_key_total_commands_processed)
        out.total_commands_processed = unsigned_number_from_string(val);
      else if (key == server_info_key_uptime_in_seconds)
        out.uptime_in_seconds = unsigned_number_from_string(val);
      else if (key == server_info_key_uptime_in_days)
        out.uptime_in_days = unsigned_number_from_string(val);
      else
        throw protocol_error(string("unexpected info key '") + key + "'");
    }
