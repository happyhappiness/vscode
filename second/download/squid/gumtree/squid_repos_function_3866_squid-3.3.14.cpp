Adaptation::Config::MetaHeader::Value::Pointer
Adaptation::Config::MetaHeader::addValue(const String &value)
{
    Value::Pointer v = new Value(value);
    values.push_back(v);
    return v;
}