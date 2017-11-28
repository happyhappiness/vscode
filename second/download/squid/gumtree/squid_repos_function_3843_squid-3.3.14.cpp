const char *
Adaptation::vectPointStr(Adaptation::VectPoint point)
{
    switch (point) {

    case Adaptation::pointPreCache:
        return "PRECACHE";
        break;

    case Adaptation::pointPostCache:
        return "POSTCACHE";
        break;

    default:
        break;
    }

    return "NONE";
}