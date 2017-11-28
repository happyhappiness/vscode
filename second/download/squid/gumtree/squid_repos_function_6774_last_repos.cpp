char const *
ESICustomParser::errorString() const
{
    if (error.size())
        return error.termedBuf();
    else
        return "Parsing error strings not implemented";
}