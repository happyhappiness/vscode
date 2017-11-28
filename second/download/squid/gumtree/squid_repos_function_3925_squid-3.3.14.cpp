libecap::shared_ptr<libecap::Message>
Adaptation::Ecap::MessageRep::clone() const
{
    HttpMsg *hdr = theMessage.header->clone();
    hdr->body_pipe = NULL; // if any; TODO: remove pipe cloning from ::clone?
    libecap::shared_ptr<libecap::Message> res(new MessageRep(hdr));

    // restore indication of a body if needed, but not the pipe
    if (theMessage.header->body_pipe != NULL)
        res->addBody();

    return res;
}