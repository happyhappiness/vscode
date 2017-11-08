static void* xml2enc_merge(apr_pool_t* pool, void* BASE, void* ADD)
{
    xml2cfg* base = BASE;
    xml2cfg* add = ADD;
    xml2cfg* ret = apr_pcalloc(pool, sizeof(xml2cfg));
    ret->default_encoding = (add->default_encoding == XML_CHAR_ENCODING_NONE)
                          ? base->default_encoding : add->default_encoding ;
    ret->default_charset = add->default_charset
                         ? add->default_charset : base->default_charset;
    ret->skipto = add->skipto ? add->skipto : base->skipto;
    return ret;
}