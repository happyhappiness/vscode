void
ClientHttpRequest::resumeBodyStorage()
{
    if (!adaptedBodySource)
        return;

    noteMoreBodyDataAvailable(adaptedBodySource);
}