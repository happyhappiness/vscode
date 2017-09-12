      if (key == server_info_key_version)
        out.version = val;
      else if (key == server_info_key_bgsave_in_progress)
        out.bgsave_in_progress = value_from_string<unsigned long>(val) == 1;
      else if (key == server_info_key_connected_clients)
        out.connected_clients = value_from_string<unsigned long>(val);
      else if (key == server_info_key_connected_slaves)
        out.connected_slaves = value_from_string<unsigned long>(val);
      else if (key == server_info_key_used_memory)
        out.used_memory = value_from_string<unsigned long>(val);
      else if (key == server_info_key_changes_since_last_save)
        out.changes_since_last_save = value_from_string<unsigned long>(val);
      else if (key == server_info_key_last_save_time)
        out.last_save_time = value_from_string<unsigned long>(val);
      else if (key == server_info_key_total_connections_received)
        out.total_connections_received = value_from_string<unsigned long>(val);
      else if (key == server_info_key_total_commands_processed)
        out.total_commands_processed = value_from_string<unsigned long>(val);
      else if (key == server_info_key_uptime_in_seconds)
        out.uptime_in_seconds = value_from_string<unsigned long>(val);
      else if (key == server_info_key_uptime_in_days)
        out.uptime_in_days = value_from_string<unsigned long>(val);
      else if (key == server_info_key_role)
        out.role = val == server_info_value_role_master ? role_master : role_slave;
      else
        throw protocol_error(string("unexpected info key '") + key + "'");
    }
