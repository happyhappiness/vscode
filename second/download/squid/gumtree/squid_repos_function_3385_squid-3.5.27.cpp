static bool Enabled(const int section, const int level)
    {
        return level <= Debug::Levels[section];
    }