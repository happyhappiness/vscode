bool
UsingSmp()
{
    return InDaemonMode() && NumberOfKids() > 1;
}