bool Adaptation::History::extractNextServices(String &value)
{
    if (theNextServices == TheNullServices)
        return false;

    value = theNextServices;
    theNextServices = TheNullServices; // prevents resetting the plan twice
    return true;
}