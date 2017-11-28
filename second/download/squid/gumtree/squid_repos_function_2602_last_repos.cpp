void
CommAcceptCbParams::print(std::ostream &os) const
{
    CommCommonCbParams::print(os);

    if (xaction != NULL)
        os << ", " << xaction->id;
}