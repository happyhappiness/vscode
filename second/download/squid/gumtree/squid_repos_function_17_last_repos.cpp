std::ostringstream &
Debug::Start(const int section, const int level)
{
    Current = new Context(section, level);
    return Current->buf;
}