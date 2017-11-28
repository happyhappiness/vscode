bool
DelayId::operator == (DelayId const &rhs) const
{
    /* Doesn't compare composites properly....
     * only use to test against default ID's
     */
    return pool_ == rhs.pool_ && compositeId == rhs.compositeId;
}