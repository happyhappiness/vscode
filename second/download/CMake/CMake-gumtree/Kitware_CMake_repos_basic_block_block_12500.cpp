{
    memcpy(packed_size, file_header.pack_size, 4);
    memcpy(packed_size + 4, p, 4); /* High pack size */
    p += 4;
    memcpy(unp_size, file_header.unp_size, 4);
    memcpy(unp_size + 4, p, 4); /* High unpack size */
    p += 4;
    rar->packed_size = archive_le64dec(&packed_size);
    rar->unp_size = archive_le64dec(&unp_size);
  }