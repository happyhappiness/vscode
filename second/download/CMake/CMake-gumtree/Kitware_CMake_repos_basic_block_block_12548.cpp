{
      if (rar->unp_offset > 0) {
        /*
         * We have unprocessed extracted data. write it out.
         */
        *buff = rar->unp_buffer;
        *size = rar->unp_offset;
        *offset = rar->offset_outgoing;
        rar->offset_outgoing += *size;
        /* Calculate File CRC. */
        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
          (unsigned)*size);
        rar->unp_offset = 0;
        return (ARCHIVE_OK);
      }
      *buff = NULL;
      *size = 0;
      *offset = rar->offset;
      if (rar->file_crc != rar->crc_calculated) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "File CRC error");
        return (ARCHIVE_FATAL);
      }
      rar->entry_eof = 1;
      return (ARCHIVE_EOF);
    }