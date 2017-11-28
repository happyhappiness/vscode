void
Adaptation::Message::ShortCircuit(Message &src, Message &dest)
{
    Must(!dest.header); // the message is not "used"
    Must(!dest.body_pipe); // can relax if needed, but need !body_pipe->used()
    Must(src.header); // or there is nothing to shortcircuit

    if (src.header->body_pipe != NULL) {
        // check that it would not be too late to shortcircuit the pipe
        Must(!src.header->body_pipe->consumedSize());
        src.header->body_pipe->clearConsumer(); // if any
        // note: current header->body_pipe producer may later become
        // dest.body_pipe consumer and consume its own data
        // TODO: consumer should detect and bypass short-circuit adaptation
    }
    dest.set(src.header->clone());
}