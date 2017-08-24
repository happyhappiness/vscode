{
    memcpy(buf, connssl->decdata_buffer, size);
    memmove(connssl->decdata_buffer, connssl->decdata_buffer + size,
            connssl->decdata_offset - size);
    connssl->decdata_offset -= size;

    infof(data, "schannel: decrypted data returned %zu\n", size);
    infof(data, "schannel: decrypted data buffer: offset %zu length %zu\n",
          connssl->decdata_offset, connssl->decdata_length);
    *err = CURLE_OK;
    return (ssize_t)size;
  }