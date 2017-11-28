Adaptation::Message &
Adaptation::Ecap::XactionRep::answer()
{
    MessageRep *rep = dynamic_cast<MessageRep*>(theAnswerRep.get());
    Must(rep);
    return rep->raw();
}