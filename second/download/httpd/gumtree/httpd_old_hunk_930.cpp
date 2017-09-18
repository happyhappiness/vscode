    * is for the algorithm to operate on the best available precision
    * regardless of who runs it.  Since the above calculation may
    * result in significant variance at 1e-12, rounding would be bogus.
    */

#ifdef NEG_DEBUG
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
           "Variant: file=%s type=%s lang=%s sourceq=%1.3f "
           "mimeq=%1.3f langq=%1.3f charq=%1.3f encq=%1.3f "
           "q=%1.5f definite=%d",            
            (variant->file_name ? variant->file_name : ""),
            (variant->mime_type ? variant->mime_type : ""),
            (variant->content_languages
             ? apr_array_pstrcat(neg->pool, variant->content_languages, ',')
             : ""),
            variant->source_quality,
