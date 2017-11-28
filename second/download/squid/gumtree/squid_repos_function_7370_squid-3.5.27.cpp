MemPools &
MemPools::GetInstance()
{
    /* Must use this idiom, as we can be double-initialised
     * if we are called during static initialisations.
     */
    if (!Instance)
        Instance = new MemPools;
    return *Instance;
}