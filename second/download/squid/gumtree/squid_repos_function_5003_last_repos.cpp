bool
Rock::Rebuild::doneValidating() const
{
    // paranoid slot checking is only enabled with squid -S
    return validationPos >= dbEntryLimit +
           (opt_store_doublecheck ? dbSlotLimit : 0);
}