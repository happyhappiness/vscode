void Ipc::Strand::start()
{
    Port::start();
    registerSelf();
}