void
Rock::HeaderUpdater::noteDoneWriting(int errflag)
{
    debugs(47, 5, errflag << " reader=" << reader);
    Must(!errflag);
    Must(!reader); // if we wrote everything, then we must have read everything

    Must(writer);
    IoState &rockWriter = dynamic_cast<IoState&>(*writer);
    update.fresh.splicingPoint = rockWriter.splicingPoint;
    debugs(47, 5, "fresh chain ends at " << update.fresh.splicingPoint);
    store->map->closeForUpdating(update);
    rockWriter.writeableAnchor_ = nullptr;
    writer = nullptr; // we are done writing

    Must(doneAll());
}