Adaptation::Ecap::HeaderRep::Value
Adaptation::Ecap::HeaderRep::value(const Name &name) const
{
    const Http::HdrType squidId = TranslateHeaderId(name);
    const String value = squidId == Http::HdrType::OTHER ?
                         theHeader.getByName(name.image().c_str()) :
                         theHeader.getStrOrList(squidId);
    return value.size() > 0 ?
           Value::FromTempString(value.termedBuf()) : Value();
}