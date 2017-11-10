static void* xml2enc_config(apr_pool_t* pool, char* x)
{
    xml2cfg* ret = apr_pcalloc(pool, sizeof(xml2cfg));
    ret->default_encoding = XML_CHAR_ENCODING_NONE ;
    return ret;
}