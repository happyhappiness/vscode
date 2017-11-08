static int InstallConsoleHandler(void)
{
    /*  Our command line handler interfaces the system operator
    with this NLM */

    NX_WRAP_INTERFACE(CommandLineInterpreter, 2, (void*)&(ConsoleHandler.parser));

    ConsoleHandler.rTag = AllocateResourceTag(getnlmhandle(), "Command Line Processor",
        ConsoleCommandSignature);
    if (!ConsoleHandler.rTag)
    {
        printf("Error on allocate resource tag\n");
        return 1;
    }

    RegisterConsoleCommand(&ConsoleHandler);

    /*  The Remove procedure unregisters the console handler */

    return 0;
}