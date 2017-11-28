         q = new CbDataList<int> (atoi(t));
         *(Tail) = q;
         Tail = &q->next;
     }
 }
 
-ACLData<IpAddress> *
+ACLData<Ip::Address> *
 ACLASN::clone() const
 {
     if (data)
         fatal ("cloning of ACLASN not implemented");
 
     return new ACLASN(*this);
 }
 
 /* explicit template instantiation required for some systems */
 
-template class ACLStrategised<IpAddress>;
+template class ACLStrategised<Ip::Address>;
 
 ACL::Prototype ACLASN::SourceRegistryProtoype(&ACLASN::SourceRegistryEntry_, "src_as");
 
-ACLStrategised<IpAddress> ACLASN::SourceRegistryEntry_(new ACLASN, ACLSourceASNStrategy::Instance(), "src_as");
+ACLStrategised<Ip::Address> ACLASN::SourceRegistryEntry_(new ACLASN, ACLSourceASNStrategy::Instance(), "src_as");
 
 ACL::Prototype ACLASN::DestinationRegistryProtoype(&ACLASN::DestinationRegistryEntry_, "dst_as");
 
-ACLStrategised<IpAddress> ACLASN::DestinationRegistryEntry_(new ACLASN, ACLDestinationASNStrategy::Instance(), "dst_as");
+ACLStrategised<Ip::Address> ACLASN::DestinationRegistryEntry_(new ACLASN, ACLDestinationASNStrategy::Instance(), "dst_as");
 
 int
-ACLSourceASNStrategy::match (ACLData<IpAddress> * &data, ACLFilledChecklist *checklist)
+ACLSourceASNStrategy::match (ACLData<Ip::Address> * &data, ACLFilledChecklist *checklist)
 {
     return data->match(checklist->src_addr);
 }
 
 ACLSourceASNStrategy *
 ACLSourceASNStrategy::Instance()
