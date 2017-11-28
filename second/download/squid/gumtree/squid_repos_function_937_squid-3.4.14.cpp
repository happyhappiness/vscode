static
void
commPlanHalfClosedCheck()
{
    if (!WillCheckHalfClosed && !TheHalfClosed->empty()) {
        eventAdd("commHalfClosedCheck", &commHalfClosedCheck, NULL, 1.0, 1);
        WillCheckHalfClosed = true;
    }
}