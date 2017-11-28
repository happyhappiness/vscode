void Adaptation::Icap::ModXact::startWriting()
{
    state.writing = State::writingConnect;

    decideOnPreview(); // must be decided before we decideOnRetries
    decideOnRetries();

    openConnection();
}