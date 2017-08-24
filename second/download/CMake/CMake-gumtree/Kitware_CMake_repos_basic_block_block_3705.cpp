{
    size_t result = decodeQuantum(pos, src);
    if(!result) {
      free(newstr);

      return CURLE_BAD_CONTENT_ENCODING;
    }

    pos += result;
    src += 4;
  }