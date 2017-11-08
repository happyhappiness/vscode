static PK11SlotInfo* nss_find_slot_by_name(const char *slot_name)
{
  PK11SlotInfo *slot;
  PR_Lock(nss_initlock);
  slot = PK11_FindSlotByName(slot_name);
  PR_Unlock(nss_initlock);
  return slot;
}