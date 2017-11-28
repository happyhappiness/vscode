void
UFSSwapDir::dumpEntry(StoreEntry &e) const
{
    debugs(47, 0, "UFSSwapDir::dumpEntry: FILENO "<< std::setfill('0') << std::hex << std::uppercase << std::setw(8) << e.swap_filen);
    debugs(47, 0, "UFSSwapDir::dumpEntry: PATH " << fullPath(e.swap_filen, NULL)   );
    e.dump(0);
}