bool
Fs::Ufs::UFSSwapDir::IsUFSDir(SwapDir * sd)
{
    UFSSwapDir *mySD = dynamic_cast<UFSSwapDir *>(sd);
    return (mySD != 0) ;
}