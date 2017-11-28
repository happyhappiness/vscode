void
Security::HandshakeParser::parseModernRecord()
{
    const TLSPlaintext record(tkRecords);
    tkRecords.commit();

    details->tlsVersion = record.version;

    // RFC 5246: length MUST NOT exceed 2^14
    Must(record.fragment.length() <= (1 << 14));
    // RFC 5246: MUST NOT send zero-length [non-application] fragments
    Must(record.fragment.length() || record.type == ContentType::ctApplicationData);

    if (currentContentType != record.type) {
        Must(tkMessages.atEnd()); // no currentContentType leftovers
        fragments = record.fragment;
        tkMessages.reset(fragments, true); // true because more fragments may come
        currentContentType = record.type;
    } else {
        fragments.append(record.fragment);
        tkMessages.reinput(fragments, true); // true because more fragments may come
        tkMessages.rollback();
    }
    parseMessages();
}