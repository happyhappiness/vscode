static void
free_cachemgrpasswd(Mgr::ActionPasswordList ** head)
{
    delete *head;
    *head = nullptr;
}