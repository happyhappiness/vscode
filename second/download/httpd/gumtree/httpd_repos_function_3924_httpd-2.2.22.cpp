static void fix_subnet(apr_ipsubnet_t *ipsub)
{
    /* in case caller specified more bits in network address than are
     * valid according to the mask, turn off the extra bits
     */
    int i;

    for (i = 0; i < sizeof ipsub->mask / sizeof(apr_int32_t); i++) {
        ipsub->sub[i] &= ipsub->mask[i];
    }
}