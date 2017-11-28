void
BodyPipeCheckout::checkIn()
{
    assert(!checkedIn);
    pipe.checkIn(*this);
    checkedIn = true;
}