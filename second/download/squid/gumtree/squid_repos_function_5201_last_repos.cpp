bool Client::doneAll() const
{
    return  doneWithServer() &&
#if USE_ADAPTATION
            doneWithAdaptation() &&
            Adaptation::Initiator::doneAll() &&
            BodyProducer::doneAll() &&
#endif
            BodyConsumer::doneAll();
}