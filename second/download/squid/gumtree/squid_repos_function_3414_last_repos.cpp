void
Adaptation::Ecap::MessageRep::addBody()
{
    Must(!theBodyRep);
    Must(!theMessage.body_pipe); // set in tieBody()
    theBodyRep = new BodyRep(NULL);
}