const char *
Adaptation::methodStr(Adaptation::Method method)
{
    switch (method) {

    case Adaptation::methodReqmod:
        return "REQMOD";
        break;

    case Adaptation::methodRespmod:
        return "RESPMOD";
        break;

    case Adaptation::methodOptions:
        return "OPTIONS";
        break;

    default:
        break;
    }

    return "NONE";
}