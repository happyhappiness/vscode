void Adaptation::Icap::ModXact::makeAdaptedBodyPipe(const char *what)
{
    Must(!adapted.body_pipe);
    Must(!adapted.header->body_pipe);
    adapted.header->body_pipe = new BodyPipe(this);
    adapted.body_pipe = adapted.header->body_pipe;
    debugs(93, 7, HERE << "will supply " << what << " via " <<
           adapted.body_pipe << " pipe");
}