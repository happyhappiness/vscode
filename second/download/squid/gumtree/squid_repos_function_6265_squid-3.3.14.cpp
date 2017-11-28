bool Kid::hopeless() const
{
    return badFailures > badFailureLimit;
}