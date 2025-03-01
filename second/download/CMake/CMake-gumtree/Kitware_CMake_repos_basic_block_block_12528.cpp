do {
    if (!rar->valid)
      return (ARCHIVE_FATAL);
    if (rar->ppmd_eod ||
       (rar->dictionary_size && rar->offset >= rar->unp_size))
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

    if (!rar->is_ppmd_block && rar->dictionary_size && rar->bytes_uncopied > 0)
    {
      if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
        bs = rar->unp_buffer_size - rar->unp_offset;
      else
        bs = (size_t)rar->bytes_uncopied;
      ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
      if (ret != ARCHIVE_OK)
        return (ret);
      rar->offset += bs;
      rar->bytes_uncopied -= bs;
      if (*buff != NULL) {
        rar->unp_offset = 0;
        *size = rar->unp_buffer_size;
        *offset = rar->offset_outgoing;
        rar->offset_outgoing += *size;
        /* Calculate File CRC. */
        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
          (unsigned)*size);
        return (ret);
      }
      continue;
    }

    if (!rar->br.next_in &&
      (ret = rar_br_preparation(a, &(rar->br))) < ARCHIVE_WARN)
      return (ret);
    if (rar->start_new_table && ((ret = parse_codes(a)) < (ARCHIVE_WARN)))
      return (ret);

    if (rar->is_ppmd_block)
    {
      if ((sym = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
        &rar->ppmd7_context, &rar->range_dec.p)) < 0)
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Invalid symbol");
        return (ARCHIVE_FATAL);
      }
      if(sym != rar->ppmd_escape)
      {
        lzss_emit_literal(rar, sym);
        rar->bytes_uncopied++;
      }
      else
      {
        if ((code = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
          &rar->ppmd7_context, &rar->range_dec.p)) < 0)
        {
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Invalid symbol");
          return (ARCHIVE_FATAL);
        }

        switch(code)
        {
          case 0:
            rar->start_new_table = 1;
            return read_data_compressed(a, buff, size, offset);

          case 2:
            rar->ppmd_eod = 1;/* End Of ppmd Data. */
            continue;

          case 3:
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                              "Parsing filters is unsupported.");
            return (ARCHIVE_FAILED);

          case 4:
            lzss_offset = 0;
            for (i = 2; i >= 0; i--)
            {
              if ((code = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
                &rar->ppmd7_context, &rar->range_dec.p)) < 0)
              {
                archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                  "Invalid symbol");
                return (ARCHIVE_FATAL);
              }
              lzss_offset |= code << (i * 8);
            }
            if ((length = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
              &rar->ppmd7_context, &rar->range_dec.p)) < 0)
            {
              archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                "Invalid symbol");
              return (ARCHIVE_FATAL);
            }
            lzss_emit_match(rar, lzss_offset + 2, length + 32);
            rar->bytes_uncopied += length + 32;
            break;

          case 5:
            if ((length = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
              &rar->ppmd7_context, &rar->range_dec.p)) < 0)
            {
              archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                "Invalid symbol");
              return (ARCHIVE_FATAL);
            }
            lzss_emit_match(rar, 1, length + 4);
            rar->bytes_uncopied += length + 4;
            break;

         default:
           lzss_emit_literal(rar, sym);
           rar->bytes_uncopied++;
        }
      }
    }
    else
    {
      start = rar->offset;
      end = start + rar->dictionary_size;
      rar->filterstart = INT64_MAX;

      if ((actualend = expand(a, end)) < 0)
        return ((int)actualend);

      rar->bytes_uncopied = actualend - start;
      if (rar->bytes_uncopied == 0) {
          /* Broken RAR files cause this case.
          * NOTE: If this case were possible on a normal RAR file
          * we would find out where it was actually bad and
          * what we would do to solve it. */
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Internal error extracting RAR file");
          return (ARCHIVE_FATAL);
      }
    }
    if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
      bs = rar->unp_buffer_size - rar->unp_offset;
    else
      bs = (size_t)rar->bytes_uncopied;
    ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
    if (ret != ARCHIVE_OK)
      return (ret);
    rar->offset += bs;
    rar->bytes_uncopied -= bs;
    /*
     * If *buff is NULL, it means unp_buffer is not full.
     * So we have to continue extracting a RAR file.
     */
  } while (*buff == NULL);