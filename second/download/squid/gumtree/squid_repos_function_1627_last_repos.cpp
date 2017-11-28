void
BodyPipeCheckout::checkIn()
{
    assert(!checkedIn);
    thePipe.checkIn(*this);
    checkedIn = true;
}