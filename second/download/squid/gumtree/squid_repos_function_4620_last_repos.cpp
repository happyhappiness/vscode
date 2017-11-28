static bool
Ftp::CommandHasPathParameter(const SBuf &cmd)
{
    static std::set<SBuf> PathedCommands;
    if (!PathedCommands.size()) {
        PathedCommands.insert(cmdMlst());
        PathedCommands.insert(cmdMlsd());
        PathedCommands.insert(cmdStat());
        PathedCommands.insert(cmdNlst());
        PathedCommands.insert(cmdList());
        PathedCommands.insert(cmdMkd());
        PathedCommands.insert(cmdRmd());
        PathedCommands.insert(cmdDele());
        PathedCommands.insert(cmdRnto());
        PathedCommands.insert(cmdRnfr());
        PathedCommands.insert(cmdAppe());
        PathedCommands.insert(cmdStor());
        PathedCommands.insert(cmdRetr());
        PathedCommands.insert(cmdSmnt());
        PathedCommands.insert(cmdCwd());
    }

    return PathedCommands.find(cmd) != PathedCommands.end();
}