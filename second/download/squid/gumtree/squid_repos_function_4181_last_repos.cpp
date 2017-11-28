SBufList
ACL::dumpOptions()
{
    SBufList result;
    const auto &myOptions = options();
    // optimization: most ACLs do not have myOptions
    // this check also works around dump_SBufList() adding ' ' after empty items
    if (!myOptions.empty()) {
        SBufStream stream;
        stream << myOptions;
        const SBuf optionsImage = stream.buf();
        if (!optionsImage.isEmpty())
            result.push_back(optionsImage);
    }
    return result;
}