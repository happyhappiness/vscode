DelayId::operator bool() const
{
    return pool_ || compositeId.getRaw();
}