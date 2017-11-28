void
Fs::Ufs::UFSSwapDir::unlinkFile(sfileno f)
{
    debugs(79, 3, HERE << "unlinking fileno " <<  std::setfill('0') <<
           std::hex << std::uppercase << std::setw(8) << f << " '" <<
           fullPath(f,NULL) << "'");
    /* commonUfsDirMapBitReset(this, f); */
    IO->unlinkFile(fullPath(f,NULL));
}