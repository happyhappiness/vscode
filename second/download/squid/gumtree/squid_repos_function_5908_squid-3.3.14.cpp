void ESIContext::finishRead()
{
    assert (reading_);
    reading_ = false;
}