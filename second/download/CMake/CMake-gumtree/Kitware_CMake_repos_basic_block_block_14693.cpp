{
#if HAVE_SUN_ACL
					ace->a_flags |=
					    acl_inherit_map[i].platform_inherit;
#else	/* !HAVE_SUN_ACL */
					if (acl_add_flag_np(acl_flagset,
							acl_inherit_map[i].platform_inherit) != 0) {
						archive_set_error(a, errno,
						    "Failed to add flag to NFSv4 ACL flagset");
						ret = ARCHIVE_FAILED;
						goto exit_free;
					}
#endif	/* HAVE_SUN_ACL */
				}