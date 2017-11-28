static bool
LesserStrandByKidId(const Ipc::StrandCoord &c1, const Ipc::StrandCoord &c2)
{
    return c1.kidId < c2.kidId;
}