    va_end(args3);
}

static void
_db_print_stderr(const char *format, va_list args)
{
    if (1 < Debug::Level())
        return;

    vfprintf(stderr, format, args);
}

void
Debug::parseOptions(char const *)
{
    return;
}

const char*
SkipBuildPrefix(const char* path)
{
    return path;
}

Debug::Context *Debug::Current = NULL;

Debug::Context::Context(const int aSection, const int aLevel):
    level(aLevel),
    sectionLevel(Levels[aSection]),
    upper(Current)
{
    buf.setf(std::ios::fixed);
    buf.precision(2);
}

std::ostringstream &
Debug::Start(const int section, const int level)
{
    Current = new Context(section, level);
    return Current->buf;
}

void
Debug::Finish()
{
    if (Current) {
        _db_print("%s\n", Current->buf.str().c_str());
        delete Current;
        Current = NULL;
    }
}

std::ostream &
Raw::print(std::ostream &os) const
{
    if (label_)
