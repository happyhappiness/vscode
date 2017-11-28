void Esi::Init()
{
    assert(!prCustom); // we should be called once

    prCustom = new ESIParser::Register("custom", &ESICustomParser::NewParser);

#if HAVE_LIBXML2
    prLibxml = new ESIParser::Register("libxml2", &ESILibxml2Parser::NewParser);
#endif

#if HAVE_LIBEXPAT
    prExpat = new ESIParser::Register("expat", &ESIExpatParser::NewParser);
#endif
}