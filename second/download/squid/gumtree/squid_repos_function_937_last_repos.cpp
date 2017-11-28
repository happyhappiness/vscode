static pid_t
GetOtherPid(File &pidFile)
{
    const auto input = pidFile.readSmall(1, 32);
    int64_t rawPid = -1;

    Parser::Tokenizer tok(input);
    if (!(tok.int64(rawPid, 10, false) && // PID digits
            (tok.skipOne(CharacterSet::CR)||true) && // optional CR (Windows/etc.)
            tok.skipOne(CharacterSet::LF) && // required end of line
            tok.atEnd())) { // no trailing garbage
        throw TexcHere(ToSBuf("Malformed ", TheFile));
    }

    debugs(50, 7, "found PID " << rawPid << " in " << TheFile);

    if (rawPid <= 1)
        throw TexcHere(ToSBuf("Bad ", TheFile, " contains unreasonably small PID value: ", rawPid));
    const auto finalPid = static_cast<pid_t>(rawPid);
    if (static_cast<int64_t>(finalPid) != rawPid)
        throw TexcHere(ToSBuf("Bad ", TheFile, " contains unreasonably large PID value: ", rawPid));

    return finalPid;
}