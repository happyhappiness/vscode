                 fatalf("Unknown service hash method\n");
             }
 
             wccp2_mask_identity_info.cache_identity.weight = 0;
             wccp2_mask_identity_info.cache_identity.status = 0;
 
-            xmemcpy(ptr, &wccp2_mask_identity_info, sizeof(struct wccp2_mask_identity_info_t));
+            memcpy(ptr, &wccp2_mask_identity_info, sizeof(struct wccp2_mask_identity_info_t));
             service_list_ptr->wccp2_identity_info_ptr = ptr;
 
             ptr += sizeof(struct wccp2_mask_identity_info_t);
             break;
 
         default:
