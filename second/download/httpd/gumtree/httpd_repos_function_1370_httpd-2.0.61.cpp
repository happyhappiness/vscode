static void *create_includes_server_config(apr_pool_t*p, server_rec *server)
{
    include_server_config *result =
        (include_server_config *)apr_palloc(p, sizeof(include_server_config));
    result->default_end_tag = ENDING_SEQUENCE;
    result->default_start_tag =STARTING_SEQUENCE;
    result->start_tag_len = sizeof(STARTING_SEQUENCE)-1;
    /* compile the pattern used by find_start_sequence */
    bndm_compile(&result->start_seq_pat, result->default_start_tag, 
                 result->start_tag_len); 

    result->undefinedEcho = apr_pstrdup(p,"(none)");
    result->undefinedEchoLen = strlen( result->undefinedEcho);
    return result; 
}