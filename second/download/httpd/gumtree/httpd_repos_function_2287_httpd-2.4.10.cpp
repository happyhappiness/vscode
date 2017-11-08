static void sniff_encoding(request_rec* r, xml2ctx* ctx)
{
    xml2cfg* cfg = NULL; /* initialise to shut compiler warnings up */
    char* p ;
    apr_bucket* cutb;
    apr_bucket* cute;
    apr_bucket* b;
    ap_regmatch_t match[2] ;
    apr_status_t rv;
    const char* ctype = r->content_type;

    if (ctype) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01430)
                      "Content-Type is %s", ctype) ;

        /* If we've got it in the HTTP headers, there's nothing to do */
        if (ctype && (p = ap_strcasestr(ctype, "charset=") , p != NULL)) {
            p += 8 ;
            if (ctx->encoding = apr_pstrndup(r->pool, p, strcspn(p, " ;") ),
                ctx->encoding) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01431)
                              "Got charset %s from HTTP headers", ctx->encoding) ;
                ctx->xml2enc = xmlParseCharEncoding(ctx->encoding);
            }
        }
    }
  
    /* to sniff, first we look for BOM */
    if (ctx->xml2enc == XML_CHAR_ENCODING_NONE) {
        ctx->xml2enc = xmlDetectCharEncoding((const xmlChar*)ctx->buf,
                                             ctx->bytes); 
        if (HAVE_ENCODING(ctx->xml2enc)) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01432)
                          "Got charset from XML rules.") ;
            ctx->encoding = xmlGetCharEncodingName(ctx->xml2enc);
        }
    }

    /* If none of the above, look for a META-thingey */
    /* also we're probably about to invalidate it, so we remove it. */
    if (ap_regexec(seek_meta_ctype, ctx->buf, 1, match, 0) == 0 ) {
        /* get markers on the start and end of the match */
        rv = apr_brigade_partition(ctx->bbsave, match[0].rm_eo, &cute);
        ap_assert(rv == APR_SUCCESS);
        rv = apr_brigade_partition(ctx->bbsave, match[0].rm_so, &cutb);
        ap_assert(rv == APR_SUCCESS);
        /* now set length of useful buf for start-of-data hooks */
        ctx->bytes = match[0].rm_so;
        if (ctx->encoding == NULL) {
            p = apr_pstrndup(r->pool, ctx->buf + match[0].rm_so,
                             match[0].rm_eo - match[0].rm_so) ;
            if (ap_regexec(seek_charset, p, 2, match, 0) == 0) {
                if (ctx->encoding = apr_pstrndup(r->pool, p+match[1].rm_so,
                                               match[1].rm_eo - match[1].rm_so),
                    ctx->encoding) {
                    ctx->xml2enc = xmlParseCharEncoding(ctx->encoding);
                    if (HAVE_ENCODING(ctx->xml2enc))
                        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01433)
                                      "Got charset %s from HTML META", ctx->encoding) ;
                }
            }
        }

        /* cut out the <meta> we're invalidating */
        while (cutb != cute) {
            b = APR_BUCKET_NEXT(cutb);
            APR_BUCKET_REMOVE(cutb);
            apr_bucket_destroy(cutb);
            cutb = b;
        }
        /* and leave a string */
        ctx->buf[ctx->bytes] = 0;
    }

    /* either it's set to something we found or it's still the default */
    /* Aaargh!  libxml2 has undocumented <META-crap> support.  So this fails
     * if metafix is not active.  Have to make it conditional.
     *
     * No, that means no-metafix breaks things.  Deal immediately with
     * this particular instance of metafix.
     */
    if (!HAVE_ENCODING(ctx->xml2enc)) {
        cfg = ap_get_module_config(r->per_dir_config, &xml2enc_module);
        if (!ctx->encoding) {
            ctx->encoding = cfg->default_charset?cfg->default_charset:"ISO-8859-1";
        }
        /* Unsupported charset. Can we get (iconv) support through apr_xlate? */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01434)
                      "Charset %s not supported by libxml2; trying apr_xlate",
                      ctx->encoding);
        if (apr_xlate_open(&ctx->convset, "UTF-8", ctx->encoding, r->pool)
            == APR_SUCCESS) {
            ctx->xml2enc = XML_CHAR_ENCODING_UTF8 ;
        } else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01435)
                          "Charset %s not supported.  Consider aliasing it?",
                          ctx->encoding) ;
        }
    }

    if (!HAVE_ENCODING(ctx->xml2enc)) {
        /* Use configuration default as a last resort */
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01436)
                  "No usable charset information; using configuration default");
        ctx->xml2enc = (cfg->default_encoding == XML_CHAR_ENCODING_NONE)
                        ? XML_CHAR_ENCODING_8859_1 : cfg->default_encoding ;
    }
    if (ctype && ctx->encoding) {
        if (ap_regexec(seek_charset, ctype, 2, match, 0)) {
            r->content_type = apr_pstrcat(r->pool, ctype, ";charset=utf-8",
                                          NULL);
        } else {
            char* str = apr_palloc(r->pool, strlen(r->content_type) + 13
                                   - (match[0].rm_eo - match[0].rm_so) + 1);
            memcpy(str, r->content_type, match[1].rm_so);
            memcpy(str + match[1].rm_so, "utf-8", 5);
            strcpy(str + match[1].rm_so + 5, r->content_type+match[1].rm_eo);
            r->content_type = str;
        }
    }
}