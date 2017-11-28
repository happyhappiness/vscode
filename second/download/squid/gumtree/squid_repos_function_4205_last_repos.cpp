void
Acl::OptionsParser::parse()
{
    flagsToSkip.clear();

    OptionExtractor oex;
    while (oex.extractOne()) {
        /* const */ auto rawName = oex.name;
        if (const Option *optionPtr = findOption(rawName)) {
            const Option &option = *optionPtr;
            if (option.configured())
                debugs(28, 7, "acl uses multiple " << rawName << " options");
            switch (option.valueExpectation)
            {
            case Option::valueNone:
                if (oex.hasValue)
                    throw TexcHere(ToSBuf("unexpected value for an ACL option: ", rawName, '=', oex.value()));
                option.configureDefault();
                break;
            case Option::valueRequired:
                if (!oex.hasValue)
                    throw TexcHere(ToSBuf("missing required value for ACL option ", rawName));
                option.configureWith(oex.value());
                break;
            case Option::valueOptional:
                if (oex.hasValue)
                    option.configureWith(oex.value());
                else
                    option.configureDefault();
                break;
            }
        }
        // else skip supported parameter flag
    }

    /* hack: regex code wants to parse all -i and +i flags itself */
    for (const auto name: flagsToSkip)
        ConfigParser::TokenPutBack(name);
}