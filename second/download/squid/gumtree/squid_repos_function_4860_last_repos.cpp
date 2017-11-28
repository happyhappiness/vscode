bool
Http::ContentLengthInterpreter::checkField(const String &rawValue)
{
    if (sawBad)
        return false; // one rotten apple is enough to spoil all of them

    // TODO: Optimize by always parsing the first integer first.
    return rawValue.pos(',') ?
           checkList(rawValue) :
           checkValue(rawValue.rawBuf(), rawValue.size());
}