static uint32_t ntpd_get_refclock_id (struct info_peer_summary const *peer_info)
{
	uint32_t addr = ntohl (peer_info->srcadr);
	uint32_t refclock_id = (addr >> 8) & 0x00FF;

	return (refclock_id);
}