void
Adaptation::Ecap::XactionRep::vbMakeMore()
{
    Must(makingVb == opOn); // cannot make more if done proxying
    // we cannot guarantee more vb, but we can check that there is a chance
    const BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL && p->stillConsuming(this)); // we are plugged in
    Must(!p->productionEnded() && p->mayNeedMoreData()); // and may get more
}