void Adaptation::History::recordXactFinish(int hid)
{
    Must(0 <= hid && hid < static_cast<int>(theEntries.size()));
    theEntries[hid].stop();
}