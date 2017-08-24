(last < sizeof(local_buffer)) {
      memcpy(local_buffer, name, last);
      local_buffer[last] = '\0';
      name = local_buffer;
    } else {
      string_buffer.append(name, last);
      name = string_buffer.c_str();
    }