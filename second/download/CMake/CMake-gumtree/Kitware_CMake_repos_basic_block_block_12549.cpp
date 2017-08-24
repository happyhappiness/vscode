(rar->unp_offset > 0) {
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