static int handle_fsize(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                        request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                        apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_finfo_t  finfo;
    apr_size_t  s_len;
    apr_bucket   *tmp_buck;
    char *parsed_string;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
                    /* XXX: if we *know* we're going to have to copy the
                     * thing off of the stack anyway, why not palloc buff
                     * instead of sticking it on the stack; then we can just
                     * use a pool bucket and skip the copy
                     */
                    char buff[50];

                    if (!(ctx->flags & FLAG_SIZE_IN_BYTES)) {
                        apr_strfsize(finfo.size, buff);
                        s_len = strlen (buff);
                    }
                    else {
                        int l, x, pos = 0;
                        char tmp_buff[50];

                        apr_snprintf(tmp_buff, sizeof(tmp_buff), 
                                     "%" APR_OFF_T_FMT, finfo.size);
                        l = strlen(tmp_buff);    /* grrr */
                        for (x = 0; x < l; x++) {
                            if (x && (!((l - x) % 3))) {
                                buff[pos++] = ',';
                            }
                            buff[pos++] = tmp_buff[x];
                        }
                        buff[pos] = '\0';
                        s_len = pos;
                    }

                    tmp_buck = apr_bucket_heap_create(buff, s_len, NULL,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
                else {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                }
            }
        }
    }
    return 0;
}