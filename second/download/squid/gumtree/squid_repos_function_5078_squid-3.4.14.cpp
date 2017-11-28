void
ACLIdent::parse()
{
    if (!data) {
        debugs(28, 3, HERE << "current is null. Creating");
        data = new ACLUserData;
    }

    data->parse();
}