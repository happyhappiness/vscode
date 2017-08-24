{
    if (!rar_br_read_ahead(a, br, 1)) {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Truncated RAR file data");
      rar->valid = 0;
      return -1;
    }
    bit = rar_br_bits(br, 1);
    rar_br_consume(br, 1);

    if (code->tree[node].branches[bit] < 0)
    {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Invalid prefix code in bitstream");
      return -1;
    }
    node = code->tree[node].branches[bit];
  }