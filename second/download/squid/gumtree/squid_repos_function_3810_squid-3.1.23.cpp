void
Adaptation::Ecap::BodyRep::tie(const BodyPipe::Pointer &aBody)
{
    Must(!theBody);
    Must(aBody != NULL);
    theBody = aBody;
}