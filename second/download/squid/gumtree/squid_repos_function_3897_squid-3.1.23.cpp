void Adaptation::Icap::ModXact::stopBackup()
{
    if (!virginBodySending.active())
        return;

    debugs(93, 7, HERE << "will no longer backup" << status());
    virginBodySending.disable();
    virginConsume();
}