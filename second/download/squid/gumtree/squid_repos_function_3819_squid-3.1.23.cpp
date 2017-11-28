void
Adaptation::Ecap::MessageRep::tieBody(Adaptation::Ecap::XactionRep *x)
{
    Must(theBodyRep != NULL); // addBody must be called first
    Must(!theMessage.header->body_pipe);
    Must(!theMessage.body_pipe);
    theMessage.header->body_pipe = new BodyPipe(x);
    theMessage.body_pipe = theMessage.header->body_pipe;
    theBodyRep->tie(theMessage.body_pipe);
}