static void
parse_YesNoNone(YesNoNone *option)
{
    int value = 0;
    parse_onoff(&value);
    option->configure(value > 0);
}