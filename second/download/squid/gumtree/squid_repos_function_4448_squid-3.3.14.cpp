void
aclDestroyAcls(ACL ** head)
{
    ACL *next = NULL;

    debugs(28, 8, "aclDestroyACLs: invoked");

    for (ACL *a = *head; a; a = next) {
        next = a->next;
        delete a;
    }

    *head = NULL;
}