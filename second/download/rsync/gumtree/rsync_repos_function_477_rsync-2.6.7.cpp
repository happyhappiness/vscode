int ZEXPORT deflate (strm, flush)
    z_streamp strm;
    int flush;
{
    int old_flush; /* value of flush param for previous deflate call */
    deflate_state *s;

    if (strm == Z_NULL || strm->state == Z_NULL ||
        flush > Z_INSERT_ONLY || flush < 0) {
        return Z_STREAM_ERROR;
    }
    s = strm->state;

    if (strm->next_out == Z_NULL ||
        (strm->next_in == Z_NULL && strm->avail_in != 0) ||
        (s->status == FINISH_STATE && flush != Z_FINISH)) {
        ERR_RETURN(strm, Z_STREAM_ERROR);
    }
    if (strm->avail_out == 0) ERR_RETURN(strm, Z_BUF_ERROR);

    s->strm = strm; /* just in case */
    old_flush = s->last_flush;
    s->last_flush = flush;

    /* Write the header */
    if (s->status == INIT_STATE) {
#ifdef GZIP
        if (s->wrap == 2) {
            strm->adler = crc32(0L, Z_NULL, 0);
            put_byte(s, 31);
            put_byte(s, 139);
            put_byte(s, 8);
            if (s->gzhead == NULL) {
                put_byte(s, 0);
                put_byte(s, 0);
                put_byte(s, 0);
                put_byte(s, 0);
                put_byte(s, 0);
                put_byte(s, s->level == 9 ? 2 :
                            (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2 ?
                             4 : 0));
                put_byte(s, OS_CODE);
                s->status = BUSY_STATE;
            }
            else {
                put_byte(s, (s->gzhead->text ? 1 : 0) +
                            (s->gzhead->hcrc ? 2 : 0) +
                            (s->gzhead->extra == Z_NULL ? 0 : 4) +
                            (s->gzhead->name == Z_NULL ? 0 : 8) +
                            (s->gzhead->comment == Z_NULL ? 0 : 16)
                        );
                put_byte(s, (Byte)(s->gzhead->time & 0xff));
                put_byte(s, (Byte)((s->gzhead->time >> 8) & 0xff));
                put_byte(s, (Byte)((s->gzhead->time >> 16) & 0xff));
                put_byte(s, (Byte)((s->gzhead->time >> 24) & 0xff));
                put_byte(s, s->level == 9 ? 2 :
                            (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2 ?
                             4 : 0));
                put_byte(s, s->gzhead->os & 0xff);
                if (s->gzhead->extra != NULL) {
                    put_byte(s, s->gzhead->extra_len & 0xff);
                    put_byte(s, (s->gzhead->extra_len >> 8) & 0xff);
                }
                if (s->gzhead->hcrc)
                    strm->adler = crc32(strm->adler, s->pending_buf,
                                        s->pending);
                s->gzindex = 0;
                s->status = EXTRA_STATE;
            }
        }
        else
#endif
        {
            uInt header = (Z_DEFLATED + ((s->w_bits-8)<<4)) << 8;
            uInt level_flags;

            if (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2)
                level_flags = 0;
            else if (s->level < 6)
                level_flags = 1;
            else if (s->level == 6)
                level_flags = 2;
            else
                level_flags = 3;
            header |= (level_flags << 6);
            if (s->strstart != 0) header |= PRESET_DICT;
            header += 31 - (header % 31);

            s->status = BUSY_STATE;
            putShortMSB(s, header);

            /* Save the adler32 of the preset dictionary: */
            if (s->strstart != 0) {
                putShortMSB(s, (uInt)(strm->adler >> 16));
                putShortMSB(s, (uInt)(strm->adler & 0xffff));
            }
            strm->adler = adler32(0L, Z_NULL, 0);
        }
    }
#ifdef GZIP
    if (s->status == EXTRA_STATE) {
        if (s->gzhead->extra != NULL) {
            uInt beg = s->pending;  /* start of bytes to update crc */

            while (s->gzindex < (s->gzhead->extra_len & 0xffff)) {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size)
                        break;
                }
                put_byte(s, s->gzhead->extra[s->gzindex]);
                s->gzindex++;
            }
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (s->gzindex == s->gzhead->extra_len) {
                s->gzindex = 0;
                s->status = NAME_STATE;
            }
        }
        else
            s->status = NAME_STATE;
    }
    if (s->status == NAME_STATE) {
        if (s->gzhead->name != NULL) {
            uInt beg = s->pending;  /* start of bytes to update crc */
            int val;

            do {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size) {
                        val = 1;
                        break;
                    }
                }
                val = s->gzhead->name[s->gzindex++];
                put_byte(s, val);
            } while (val != 0);
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (val == 0) {
                s->gzindex = 0;
                s->status = COMMENT_STATE;
            }
        }
        else
            s->status = COMMENT_STATE;
    }
    if (s->status == COMMENT_STATE) {
        if (s->gzhead->comment != NULL) {
            uInt beg = s->pending;  /* start of bytes to update crc */
            int val;

            do {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size) {
                        val = 1;
                        break;
                    }
                }
                val = s->gzhead->comment[s->gzindex++];
                put_byte(s, val);
            } while (val != 0);
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (val == 0)
                s->status = HCRC_STATE;
        }
        else
            s->status = HCRC_STATE;
    }
    if (s->status == HCRC_STATE) {
        if (s->gzhead->hcrc) {
            if (s->pending + 2 > s->pending_buf_size)
                flush_pending(strm);
            if (s->pending + 2 <= s->pending_buf_size) {
                put_byte(s, (Byte)(strm->adler & 0xff));
                put_byte(s, (Byte)((strm->adler >> 8) & 0xff));
                strm->adler = crc32(0L, Z_NULL, 0);
                s->status = BUSY_STATE;
            }
        }
        else
            s->status = BUSY_STATE;
    }
#endif

    /* Flush as much pending output as possible */
    if (s->pending != 0) {
        flush_pending(strm);
        if (strm->avail_out == 0) {
            /* Since avail_out is 0, deflate will be called again with
             * more output space, but possibly with both pending and
             * avail_in equal to zero. There won't be anything to do,
             * but this is not an error situation so make sure we
             * return OK instead of BUF_ERROR at next call of deflate:
             */
            s->last_flush = -1;
            return Z_OK;
        }

    /* Make sure there is something to do and avoid dup