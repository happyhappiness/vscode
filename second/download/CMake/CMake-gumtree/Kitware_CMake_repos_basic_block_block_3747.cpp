{
    /* Let zlib handle the gzip decompression entirely */
    z->next_in = (Bytef *)k->str;
    z->avail_in = (uInt)nread;
    /* Now uncompress the data */
    return inflate_stream(conn, k);
  }