void Ipc::Strand::handleRegistrationResponse(const HereIamMessage &msg)
{
    // handle registration response from the coordinator; it could be stale
    if (msg.strand.kidId == KidIdentifier && msg.strand.pid == getpid()) {
        debugs(54, 6, "kid" << KidIdentifier << " registered");
        clearTimeout(); // we are done
    } else {
        // could be an ACK to the registration message of our dead predecessor
        debugs(54, 6, "kid" << KidIdentifier << " is not yet registered");
        // keep listening, with a timeout
    }
}