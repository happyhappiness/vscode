static void RemoveConsoleHandler(void)
{
    UnRegisterConsoleCommand(&ConsoleHandler);
    NX_UNWRAP_INTERFACE(ConsoleHandler.parser);
}