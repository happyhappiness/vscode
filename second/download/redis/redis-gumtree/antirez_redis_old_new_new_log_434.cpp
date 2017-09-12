serverLog(LL_WARNING,
            "Fatal: AOF method for module data type '%s' tried to "
            "emit unknown command '%s'",
            io->type->name, cmdname);