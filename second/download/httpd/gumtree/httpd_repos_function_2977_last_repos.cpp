static void slot_done(h2_slot *slot)
{
    push_slot(&(slot->workers->zombies), slot);
}