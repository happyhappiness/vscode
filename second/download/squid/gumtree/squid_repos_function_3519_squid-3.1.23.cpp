void
ConnStateData::expectNoForwarding()
{
    if (bodyPipe != NULL) {
        debugs(33, 4, HERE << "no consumer for virgin body " << bodyPipe->status());
        bodyPipe->expectNoConsumption();
    }
}