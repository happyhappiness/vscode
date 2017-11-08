static int add_stream(h2_stream *stream, void *ctx)
{
    stream_ctx_t *x = ctx;
    int32_t flowIn, flowOut;
    
    flowIn = nghttp2_session_get_stream_effective_local_window_size(x->s->ngh2, stream->id); 
    flowOut = nghttp2_session_get_stream_remote_window_size(x->s->ngh2, stream->id);
    bbout(x->bb, "%s\n    \"%d\": {\n", (x->idx? "," : ""), stream->id);
    bbout(x->bb, "    \"state\": \"%s\",\n", h2_stream_state_str(stream));
    bbout(x->bb, "    \"created\": %f,\n", ((double)stream->created)/APR_USEC_PER_SEC);
    bbout(x->bb, "    \"flowIn\": %d,\n", flowIn);
    bbout(x->bb, "    \"flowOut\": %d,\n", flowOut);
    bbout(x->bb, "    \"dataIn\": %"APR_UINT64_T_FMT",\n", stream->in_data_octets);  
    bbout(x->bb, "    \"dataOut\": %"APR_UINT64_T_FMT"\n", stream->out_data_octets);  
    bbout(x->bb, "    }");
    
    ++x->idx;
    return 1;
}