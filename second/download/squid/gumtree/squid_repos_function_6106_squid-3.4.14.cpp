ESIParser::Pointer
ESIParser::NewParser(ESIParserClient *aClient)
{
    if (Parser == NULL) {
        Parser = Parsers;

        while (Parser != NULL && strcasecmp(Parser->name, Type) != 0)
            Parser = Parser->next;

        if (Parser == NULL)
            fatal ("Unknown ESI Parser type");
    }

    return (Parser->newParser)(aClient);
}