
    /* First though, eliminate this variant if it is not
     * acceptable by type, charset, encoding or language.
     */

#ifdef NEG_DEBUG
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
           "Variant: file=%s type=%s lang=%s sourceq=%1.3f "
           "mimeq=%1.3f langq=%1.3f langidx=%d charq=%1.3f encq=%1.3f ",
            (variant->file_name ? variant->file_name : ""),
            (variant->mime_type ? variant->mime_type : ""),
            (variant->content_languages
             ? apr_array_pstrcat(neg->pool, variant->content_languages, ',')
