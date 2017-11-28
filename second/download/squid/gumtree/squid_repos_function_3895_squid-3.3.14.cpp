Adaptation::Ecap::HeaderRep::Value
Adaptation::Ecap::HeaderRep::value(const Name &name) const
{
    const http_hdr_type squidId = TranslateHeaderId(name);
    const String value = squidId == HDR_OTHER ?
                         theHeader.getByName(name.image().c_str()) :
                         theHeader.getStrOrList(squidId);
    return value.defined() ?
           Value::FromTempString(value.termedBuf()) : Value();
}