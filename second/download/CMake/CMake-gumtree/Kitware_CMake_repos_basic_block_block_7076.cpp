f(reallocated_buffer == NULL) {
      failf(data, "schannel: unable to re-allocate memory");
      return CURLE_OUT_OF_MEMORY;
    }
    else {
      connssl->encdata_buffer = reallocated_buffer;
      connssl->encdata_length = reallocated_length;
    }