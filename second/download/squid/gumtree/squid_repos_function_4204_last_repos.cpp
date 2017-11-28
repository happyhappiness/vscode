const Acl::Option *
Acl::OptionsParser::findOption(/* const */ SBuf &rawNameBuf)
{
    // TODO: new std::map::find() in C++14 does not require this conversion
    const auto rawName = rawNameBuf.c_str();

    const auto optionPos = options_.find(rawName);
    if (optionPos != options_.end())
        return optionPos->second;

    const auto flagPos = parameterFlags_.find(rawName);
    if (flagPos != parameterFlags_.end()) {
        flagsToSkip.push_back(*flagPos); // *flagPos is permanent unlike rawName
        return nullptr;
    }

    throw TexcHere(ToSBuf("unsupported ACL option: ", rawNameBuf));
}