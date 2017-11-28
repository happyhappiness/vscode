ESIStreamContext *
ESIStreamContextNew (ESIIncludePtr include)
{
    ESIStreamContext *rv = new ESIStreamContext;
    rv->include = include;
    return rv;
}