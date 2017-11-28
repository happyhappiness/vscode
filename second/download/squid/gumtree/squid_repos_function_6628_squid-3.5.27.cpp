char const *
ESILibxml2Parser::errorString() const
{
    xmlErrorPtr error = xmlGetLastError();

    if (error == NULL)
        return NULL;

    return error->message;
}