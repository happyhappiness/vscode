static int regerr(sed_commands_t *commands, int err)
{
    switch(err) {
    case 0:
        /* No error */
        break;
    case 11:
        comperr(commands, "Range endpoint too large: %s");
        break;

    case 16:
        comperr(commands, "Bad number: %s");
        break;

    case 25:
        comperr(commands, "``\\digit'' out of range: %s");
        break;

    case 36:
        comperr(commands, "Illegal or missing delimiter: %s");
        break;

    case 41:
        comperr(commands, "No remembered search string: %s");
        break;

    case 42:
        comperr(commands, "\\( \\) imbalance: %s");
        break;

    case 43:
        comperr(commands, "Too many \\(: %s");
        break;

    case 44:
        comperr(commands, "More than 2 numbers given in \\{ \\}: %s");
        break;

    case 45:
        comperr(commands, "} expected after \\: %s");
        break;

    case 46:
        comperr(commands, "First number exceeds second in \\{ \\}: %s");
        break;

    case 49:
        comperr(commands, "[ ] imbalance: %s");
        break;

    case 50:
        comperr(commands, SEDERR_TMMES);
        break;

    default:
        comperr(commands, "Unknown regexp error code %s\n");
        break;
    }
    return (0);
}