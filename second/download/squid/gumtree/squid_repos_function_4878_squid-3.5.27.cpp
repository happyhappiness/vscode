void
ACLExtUser::parse()
{
    debugs(28, 3, "aclParseUserList: current is null. Creating");
    data = new ACLUserData;
    data->parse();
}