static void add_push(apr_bucket_brigade *bb, h2_session *s, 
                     h2_stream *stream, int last) 
{
    h2_push_diary *diary;
    apr_status_t status;
    
    bbout(bb, "    \"push\": {\n");
    diary = s->push_diary;
    if (diary) {
        const char *data;
        const char *base64_digest;
        apr_size_t len;
        
        status = h2_push_diary_digest_get(diary, bb->p, 256, 
                                          stream->request->authority, 
                                          &data, &len);
        if (status == APR_SUCCESS) {
            base64_digest = h2_util_base64url_encode(data, len, bb->p);
            bbout(bb, "      \"cacheDigest\": \"%s\",\n", base64_digest);
        }
    }
    bbout(bb, "      \"promises\": %d,\n", s->pushes_promised);
    bbout(bb, "      \"submits\": %d,\n", s->pushes_submitted);
    bbout(bb, "      \"resets\": %d\n", s->pushes_reset);
    bbout(bb, "    }%s\n", last? "" : ",");
}