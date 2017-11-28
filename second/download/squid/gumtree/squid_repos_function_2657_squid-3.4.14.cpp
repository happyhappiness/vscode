String
ProcessRoles()
{
    String roles = "";
    if (IamMasterProcess())
        roles.append(" master");
    if (IamCoordinatorProcess())
        roles.append(" coordinator");
    if (IamWorkerProcess())
        roles.append(" worker");
    if (IamDiskProcess())
        roles.append(" disker");
    return roles;
}