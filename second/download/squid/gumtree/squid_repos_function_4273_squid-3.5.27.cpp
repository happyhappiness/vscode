static
void ServiceRep_noteTimeToUpdate(void *data)
{
    Adaptation::Icap::ServiceRep *service = static_cast<Adaptation::Icap::ServiceRep*>(data);
    Must(service);
    service->noteTimeToUpdate();
}