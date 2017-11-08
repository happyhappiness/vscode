apr_status_t ajp_msg_dump(apr_pool_t *pool, ajp_msg_t *msg, char *err,
                          apr_size_t count, char **buf)
{
    apr_size_t  i, j;
    char        *current;
    apr_size_t  bl, rl;
    apr_byte_t  x;
    apr_size_t  len = msg->len;
    apr_size_t  line_len;

    /* Display only first "count" bytes */
    if (len > count)
        len = count;
         /* First the space needed for the first line */
    bl = strlen(err) + 3 * (strlen(" XXX=") + 20) + 1 +
         /* Now for the data lines */
         (len + 15) / 16 * AJP_MSG_DUMP_LINE_LENGTH;
    *buf = apr_palloc(pool, bl);
    if (!*buf)
        return APR_ENOMEM;
    apr_snprintf(*buf, bl,
                 "%s pos=%" APR_SIZE_T_FMT
                 " len=%" APR_SIZE_T_FMT " max=%" APR_SIZE_T_FMT "\n",
                 err, msg->pos, msg->len, msg->max_size);
    current = *buf + strlen(*buf);
    for (i = 0; i < len; i += AJP_MSG_DUMP_BYTES_PER_LINE) {
        /* Safety check: do we have enough buffer for another line? */
        rl = bl - (current - *buf);
        if (AJP_MSG_DUMP_LINE_LENGTH > rl) {
            *(current - 1) = '\0';
            return APR_ENOMEM;
        }
        apr_snprintf(current, rl, "%.4lx    ", (unsigned long)i);
        current += AJP_MSG_DUMP_PREFIX_LENGTH;
        line_len = len - i;
        if (line_len > AJP_MSG_DUMP_BYTES_PER_LINE) {
            line_len = AJP_MSG_DUMP_BYTES_PER_LINE;
        }
        for (j = 0; j < line_len; j++) {
            x = msg->buf[i + j];

            *current++ = hex_table[x >> 4];
            *current++ = hex_table[x & 0x0f];
            *current++ = ' ';
        }
        *current++ = ' ';
        *current++ = '-';
        *current++ = ' ';
        for (j = 0; j < line_len; j++) {
            x = msg->buf[i + j];

            if (x > 0x20 && x < 0x7F) {
                *current++ = x;
            }
            else {
                *current++ = '.';
            }
        }
        *current++ = '\n';
    }
    *(current - 1) = '\0';

    return APR_SUCCESS;
}