; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/if2ip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.sockaddr = type { i16, [14 x i8] }
%struct.ifreq = type { %union.anon, %union.anon.0 }
%union.anon = type { [16 x i8] }
%union.anon.0 = type { %struct.ifmap }
%struct.ifmap = type { i64, i64, i16, i8, i8, i8 }
%struct.in_addr = type { i32 }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }

; Function Attrs: nounwind uwtable
define i32 @Curl_ipv6_scope(%struct.sockaddr* %sa) #0 !dbg !47 {
entry:
  %sa.addr = alloca %struct.sockaddr*, align 8
  store %struct.sockaddr* %sa, %struct.sockaddr** %sa.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %sa.addr, metadata !77, metadata !78), !dbg !79
  %0 = load %struct.sockaddr*, %struct.sockaddr** %sa.addr, align 8, !dbg !80
  ret i32 0, !dbg !81
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_if_is_interface_name(i8* %interf) #0 !dbg !62 {
entry:
  %interf.addr = alloca i8*, align 8
  %buf = alloca [256 x i8], align 16
  store i8* %interf, i8** %interf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interf.addr, metadata !82, metadata !78), !dbg !83
  call void @llvm.dbg.declare(metadata [256 x i8]* %buf, metadata !84, metadata !78), !dbg !88
  %0 = load i8*, i8** %interf.addr, align 8, !dbg !89
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %buf, i32 0, i32 0, !dbg !90
  %call = call i32 @Curl_if2ip(i32 2, i32 0, i32 0, i8* %0, i8* %arraydecay, i32 256), !dbg !91
  %cmp = icmp eq i32 %call, 0, !dbg !92
  %cond = select i1 %cmp, i32 0, i32 1, !dbg !93
  %tobool = icmp ne i32 %cond, 0, !dbg !93
  ret i1 %tobool, !dbg !94
}

; Function Attrs: nounwind uwtable
define i32 @Curl_if2ip(i32 %af, i32 %remote_scope, i32 %remote_scope_id, i8* %interf, i8* %buf, i32 %buf_size) #0 !dbg !68 {
entry:
  %retval = alloca i32, align 4
  %af.addr = alloca i32, align 4
  %remote_scope.addr = alloca i32, align 4
  %remote_scope_id.addr = alloca i32, align 4
  %interf.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %buf_size.addr = alloca i32, align 4
  %req = alloca %struct.ifreq, align 8
  %in = alloca %struct.in_addr, align 4
  %s = alloca %struct.sockaddr_in*, align 8
  %dummy = alloca i32, align 4
  %len = alloca i64, align 8
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !95, metadata !78), !dbg !96
  store i32 %remote_scope, i32* %remote_scope.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %remote_scope.addr, metadata !97, metadata !78), !dbg !98
  store i32 %remote_scope_id, i32* %remote_scope_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %remote_scope_id.addr, metadata !99, metadata !78), !dbg !100
  store i8* %interf, i8** %interf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interf.addr, metadata !101, metadata !78), !dbg !102
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !103, metadata !78), !dbg !104
  store i32 %buf_size, i32* %buf_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %buf_size.addr, metadata !105, metadata !78), !dbg !106
  call void @llvm.dbg.declare(metadata %struct.ifreq* %req, metadata !107, metadata !78), !dbg !145
  call void @llvm.dbg.declare(metadata %struct.in_addr* %in, metadata !146, metadata !78), !dbg !147
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %s, metadata !148, metadata !78), !dbg !149
  call void @llvm.dbg.declare(metadata i32* %dummy, metadata !150, metadata !78), !dbg !153
  call void @llvm.dbg.declare(metadata i64* %len, metadata !154, metadata !78), !dbg !157
  %0 = load i32, i32* %remote_scope.addr, align 4, !dbg !158
  %1 = load i32, i32* %remote_scope_id.addr, align 4, !dbg !159
  %2 = load i8*, i8** %interf.addr, align 8, !dbg !160
  %tobool = icmp ne i8* %2, null, !dbg !160
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !162

lor.lhs.false:                                    ; preds = %entry
  %3 = load i32, i32* %af.addr, align 4, !dbg !163
  %cmp = icmp ne i32 %3, 2, !dbg !165
  br i1 %cmp, label %if.then, label %if.end, !dbg !166

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !167
  br label %return, !dbg !167

if.end:                                           ; preds = %lor.lhs.false
  %4 = load i8*, i8** %interf.addr, align 8, !dbg !168
  %call = call i64 @strlen(i8* %4) #6, !dbg !169
  store i64 %call, i64* %len, align 8, !dbg !170
  %5 = load i64, i64* %len, align 8, !dbg !171
  %cmp1 = icmp uge i64 %5, 16, !dbg !173
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !174

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !175
  br label %return, !dbg !175

if.end3:                                          ; preds = %if.end
  %call4 = call i32 @socket(i32 2, i32 1, i32 0) #7, !dbg !176
  store i32 %call4, i32* %dummy, align 4, !dbg !177
  %6 = load i32, i32* %dummy, align 4, !dbg !178
  %cmp5 = icmp eq i32 -1, %6, !dbg !180
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !181

if.then6:                                         ; preds = %if.end3
  store i32 0, i32* %retval, align 4, !dbg !182
  br label %return, !dbg !182

if.end7:                                          ; preds = %if.end3
  %7 = bitcast %struct.ifreq* %req to i8*, !dbg !183
  call void @llvm.memset.p0i8.i64(i8* %7, i8 0, i64 40, i32 8, i1 false), !dbg !183
  %ifr_ifrn = getelementptr inbounds %struct.ifreq, %struct.ifreq* %req, i32 0, i32 0, !dbg !184
  %ifrn_name = bitcast %union.anon* %ifr_ifrn to [16 x i8]*, !dbg !184
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %ifrn_name, i32 0, i32 0, !dbg !185
  %8 = load i8*, i8** %interf.addr, align 8, !dbg !186
  %9 = load i64, i64* %len, align 8, !dbg !187
  %add = add i64 %9, 1, !dbg !188
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %8, i64 %add, i32 1, i1 false), !dbg !185
  %ifr_ifru = getelementptr inbounds %struct.ifreq, %struct.ifreq* %req, i32 0, i32 1, !dbg !189
  %ifru_addr = bitcast %union.anon.0* %ifr_ifru to %struct.sockaddr*, !dbg !189
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %ifru_addr, i32 0, i32 0, !dbg !190
  store i16 2, i16* %sa_family, align 8, !dbg !191
  %10 = load i32, i32* %dummy, align 4, !dbg !192
  %call8 = call i32 (i32, i64, ...) @ioctl(i32 %10, i64 35093, %struct.ifreq* %req) #7, !dbg !194
  %cmp9 = icmp slt i32 %call8, 0, !dbg !195
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !196

if.then10:                                        ; preds = %if.end7
  %11 = load i32, i32* %dummy, align 4, !dbg !197
  %call11 = call i32 @close(i32 %11), !dbg !197
  store i32 0, i32* %retval, align 4, !dbg !199
  br label %return, !dbg !199

if.end12:                                         ; preds = %if.end7
  %ifr_ifru13 = getelementptr inbounds %struct.ifreq, %struct.ifreq* %req, i32 0, i32 1, !dbg !200
  %ifru_addr14 = bitcast %union.anon.0* %ifr_ifru13 to %struct.sockaddr*, !dbg !200
  %12 = bitcast %struct.sockaddr* %ifru_addr14 to %struct.sockaddr_in*, !dbg !201
  store %struct.sockaddr_in* %12, %struct.sockaddr_in** %s, align 8, !dbg !202
  %13 = bitcast %struct.in_addr* %in to i8*, !dbg !203
  %14 = load %struct.sockaddr_in*, %struct.sockaddr_in** %s, align 8, !dbg !204
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %14, i32 0, i32 2, !dbg !205
  %15 = bitcast %struct.in_addr* %sin_addr to i8*, !dbg !203
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %15, i64 4, i32 4, i1 false), !dbg !203
  %16 = load %struct.sockaddr_in*, %struct.sockaddr_in** %s, align 8, !dbg !206
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %16, i32 0, i32 0, !dbg !207
  %17 = load i16, i16* %sin_family, align 4, !dbg !207
  %conv = zext i16 %17 to i32, !dbg !206
  %18 = bitcast %struct.in_addr* %in to i8*, !dbg !208
  %19 = load i8*, i8** %buf.addr, align 8, !dbg !209
  %20 = load i32, i32* %buf_size.addr, align 4, !dbg !210
  %conv15 = sext i32 %20 to i64, !dbg !210
  %call16 = call i8* @Curl_inet_ntop(i32 %conv, i8* %18, i8* %19, i64 %conv15), !dbg !211
  %21 = load i32, i32* %dummy, align 4, !dbg !212
  %call17 = call i32 @close(i32 %21), !dbg !212
  store i32 2, i32* %retval, align 4, !dbg !213
  br label %return, !dbg !213

return:                                           ; preds = %if.end12, %if.then10, %if.then6, %if.then2, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !214
  ret i32 %22, !dbg !214
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: nounwind
declare i32 @socket(i32, i32, i32) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #3

declare i32 @close(i32) #5

declare i8* @Curl_inet_ntop(i32, i8*, i8*, i64) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!74, !75}
!llvm.ident = !{!76}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !21, subprograms: !46)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/if2ip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !9}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 36, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/if2ip.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8}
!6 = !DIEnumerator(name: "IF2IP_NOT_FOUND", value: 0)
!7 = !DIEnumerator(name: "IF2IP_AF_NOT_SUPPORTED", value: 1)
!8 = !DIEnumerator(name: "IF2IP_FOUND", value: 2)
!9 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !10, line: 24, size: 32, align: 32, elements: !11)
!10 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!11 = !{!12, !13, !14, !15, !16, !17, !18, !19, !20}
!12 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!13 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!14 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!15 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!16 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!17 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!18 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!19 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!20 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!21 = !{!22}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !24, line: 237, size: 128, align: 32, elements: !25)
!24 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!25 = !{!26, !30, !34, !41}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !23, file: !24, line: 239, baseType: !27, size: 16, align: 16)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !28, line: 28, baseType: !29)
!28 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!29 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !23, file: !24, line: 240, baseType: !31, size: 16, align: 16, offset: 16)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !24, line: 117, baseType: !32)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !33, line: 49, baseType: !29)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!34 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !23, file: !24, line: 241, baseType: !35, size: 32, align: 32, offset: 32)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !24, line: 31, size: 32, align: 32, elements: !36)
!36 = !{!37}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !35, file: !24, line: 33, baseType: !38, size: 32, align: 32)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !24, line: 30, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !40)
!40 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !23, file: !24, line: 244, baseType: !42, size: 64, align: 8, offset: 64)
!42 = !DICompositeType(tag: DW_TAG_array_type, baseType: !43, size: 64, align: 8, elements: !44)
!43 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!44 = !{!45}
!45 = !DISubrange(count: 8)
!46 = !{!47, !62, !68}
!47 = distinct !DISubprogram(name: "Curl_ipv6_scope", scope: !1, file: !1, line: 64, type: !48, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !61)
!48 = !DISubroutineType(types: !49)
!49 = !{!40, !50}
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !52)
!52 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !53, line: 149, size: 128, align: 16, elements: !54)
!53 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!54 = !{!55, !56}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !52, file: !53, line: 151, baseType: !27, size: 16, align: 16)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !52, file: !53, line: 152, baseType: !57, size: 112, align: 8, offset: 16)
!57 = !DICompositeType(tag: DW_TAG_array_type, baseType: !58, size: 112, align: 8, elements: !59)
!58 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!59 = !{!60}
!60 = !DISubrange(count: 14)
!61 = !{}
!62 = distinct !DISubprogram(name: "Curl_if_is_interface_name", scope: !1, file: !1, line: 197, type: !63, isLocal: false, isDefinition: true, scopeLine: 198, flags: DIFlagPrototyped, isOptimized: false, variables: !61)
!63 = !DISubroutineType(types: !64)
!64 = !{!65, !66}
!65 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !58)
!68 = distinct !DISubprogram(name: "Curl_if2ip", scope: !1, file: !1, line: 206, type: !69, isLocal: false, isDefinition: true, scopeLine: 209, flags: DIFlagPrototyped, isOptimized: false, variables: !61)
!69 = !DISubroutineType(types: !70)
!70 = !{!71, !72, !40, !40, !66, !73, !72}
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "if2ip_result_t", file: !4, line: 40, baseType: !3)
!72 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!74 = !{i32 2, !"Dwarf Version", i32 4}
!75 = !{i32 2, !"Debug Info Version", i32 3}
!76 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!77 = !DILocalVariable(name: "sa", arg: 1, scope: !47, file: !1, line: 64, type: !50)
!78 = !DIExpression()
!79 = !DILocation(line: 64, column: 53, scope: !47)
!80 = !DILocation(line: 67, column: 10, scope: !47)
!81 = !DILocation(line: 91, column: 3, scope: !47)
!82 = !DILocalVariable(name: "interf", arg: 1, scope: !62, file: !1, line: 197, type: !66)
!83 = !DILocation(line: 197, column: 44, scope: !62)
!84 = !DILocalVariable(name: "buf", scope: !62, file: !1, line: 200, type: !85)
!85 = !DICompositeType(tag: DW_TAG_array_type, baseType: !58, size: 2048, align: 8, elements: !86)
!86 = !{!87}
!87 = !DISubrange(count: 256)
!88 = !DILocation(line: 200, column: 8, scope: !62)
!89 = !DILocation(line: 202, column: 50, scope: !62)
!90 = !DILocation(line: 202, column: 58, scope: !62)
!91 = !DILocation(line: 202, column: 11, scope: !62)
!92 = !DILocation(line: 202, column: 76, scope: !62)
!93 = !DILocation(line: 202, column: 10, scope: !62)
!94 = !DILocation(line: 202, column: 3, scope: !62)
!95 = !DILocalVariable(name: "af", arg: 1, scope: !68, file: !1, line: 206, type: !72)
!96 = !DILocation(line: 206, column: 31, scope: !68)
!97 = !DILocalVariable(name: "remote_scope", arg: 2, scope: !68, file: !1, line: 206, type: !40)
!98 = !DILocation(line: 206, column: 48, scope: !68)
!99 = !DILocalVariable(name: "remote_scope_id", arg: 3, scope: !68, file: !1, line: 207, type: !40)
!100 = !DILocation(line: 207, column: 40, scope: !68)
!101 = !DILocalVariable(name: "interf", arg: 4, scope: !68, file: !1, line: 207, type: !66)
!102 = !DILocation(line: 207, column: 69, scope: !68)
!103 = !DILocalVariable(name: "buf", arg: 5, scope: !68, file: !1, line: 208, type: !73)
!104 = !DILocation(line: 208, column: 33, scope: !68)
!105 = !DILocalVariable(name: "buf_size", arg: 6, scope: !68, file: !1, line: 208, type: !72)
!106 = !DILocation(line: 208, column: 42, scope: !68)
!107 = !DILocalVariable(name: "req", scope: !68, file: !1, line: 210, type: !108)
!108 = !DICompositeType(tag: DW_TAG_structure_type, name: "ifreq", file: !109, line: 126, size: 320, align: 64, elements: !110)
!109 = !DIFile(filename: "/usr/include/net/if.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!110 = !{!111, !118}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "ifr_ifrn", scope: !108, file: !109, line: 133, baseType: !112, size: 128, align: 8)
!112 = !DICompositeType(tag: DW_TAG_union_type, scope: !108, file: !109, line: 130, size: 128, align: 8, elements: !113)
!113 = !{!114}
!114 = !DIDerivedType(tag: DW_TAG_member, name: "ifrn_name", scope: !112, file: !109, line: 132, baseType: !115, size: 128, align: 8)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !58, size: 128, align: 8, elements: !116)
!116 = !{!117}
!117 = !DISubrange(count: 16)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "ifr_ifru", scope: !108, file: !109, line: 149, baseType: !119, size: 192, align: 64, offset: 128)
!119 = !DICompositeType(tag: DW_TAG_union_type, scope: !108, file: !109, line: 135, size: 192, align: 64, elements: !120)
!120 = !{!121, !122, !123, !124, !125, !126, !128, !129, !130, !140, !141, !142}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_addr", scope: !119, file: !109, line: 137, baseType: !52, size: 128, align: 16)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_dstaddr", scope: !119, file: !109, line: 138, baseType: !52, size: 128, align: 16)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_broadaddr", scope: !119, file: !109, line: 139, baseType: !52, size: 128, align: 16)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_netmask", scope: !119, file: !109, line: 140, baseType: !52, size: 128, align: 16)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_hwaddr", scope: !119, file: !109, line: 141, baseType: !52, size: 128, align: 16)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_flags", scope: !119, file: !109, line: 142, baseType: !127, size: 16, align: 16)
!127 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_ivalue", scope: !119, file: !109, line: 143, baseType: !72, size: 32, align: 32)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_mtu", scope: !119, file: !109, line: 144, baseType: !72, size: 32, align: 32)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_map", scope: !119, file: !109, line: 145, baseType: !131, size: 192, align: 64)
!131 = !DICompositeType(tag: DW_TAG_structure_type, name: "ifmap", file: !109, line: 111, size: 192, align: 64, elements: !132)
!132 = !{!133, !135, !136, !137, !138, !139}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "mem_start", scope: !131, file: !109, line: 113, baseType: !134, size: 64, align: 64)
!134 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "mem_end", scope: !131, file: !109, line: 114, baseType: !134, size: 64, align: 64, offset: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "base_addr", scope: !131, file: !109, line: 115, baseType: !29, size: 16, align: 16, offset: 128)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "irq", scope: !131, file: !109, line: 116, baseType: !43, size: 8, align: 8, offset: 144)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "dma", scope: !131, file: !109, line: 117, baseType: !43, size: 8, align: 8, offset: 152)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !131, file: !109, line: 118, baseType: !43, size: 8, align: 8, offset: 160)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_slave", scope: !119, file: !109, line: 146, baseType: !115, size: 128, align: 8)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_newname", scope: !119, file: !109, line: 147, baseType: !115, size: 128, align: 8)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "ifru_data", scope: !119, file: !109, line: 148, baseType: !143, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "__caddr_t", file: !144, line: 183, baseType: !73)
!144 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!145 = !DILocation(line: 210, column: 16, scope: !68)
!146 = !DILocalVariable(name: "in", scope: !68, file: !1, line: 211, type: !35)
!147 = !DILocation(line: 211, column: 18, scope: !68)
!148 = !DILocalVariable(name: "s", scope: !68, file: !1, line: 212, type: !22)
!149 = !DILocation(line: 212, column: 23, scope: !68)
!150 = !DILocalVariable(name: "dummy", scope: !68, file: !1, line: 213, type: !151)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !152, line: 131, baseType: !72)
!152 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!153 = !DILocation(line: 213, column: 17, scope: !68)
!154 = !DILocalVariable(name: "len", scope: !68, file: !1, line: 214, type: !155)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !156, line: 62, baseType: !134)
!156 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!157 = !DILocation(line: 214, column: 10, scope: !68)
!158 = !DILocation(line: 216, column: 9, scope: !68)
!159 = !DILocation(line: 217, column: 9, scope: !68)
!160 = !DILocation(line: 219, column: 7, scope: !161)
!161 = distinct !DILexicalBlock(scope: !68, file: !1, line: 219, column: 6)
!162 = !DILocation(line: 219, column: 14, scope: !161)
!163 = !DILocation(line: 219, column: 18, scope: !164)
!164 = !DILexicalBlockFile(scope: !161, file: !1, discriminator: 1)
!165 = !DILocation(line: 219, column: 21, scope: !164)
!166 = !DILocation(line: 219, column: 6, scope: !164)
!167 = !DILocation(line: 220, column: 5, scope: !161)
!168 = !DILocation(line: 222, column: 16, scope: !68)
!169 = !DILocation(line: 222, column: 9, scope: !68)
!170 = !DILocation(line: 222, column: 7, scope: !68)
!171 = !DILocation(line: 223, column: 6, scope: !172)
!172 = distinct !DILexicalBlock(scope: !68, file: !1, line: 223, column: 6)
!173 = !DILocation(line: 223, column: 10, scope: !172)
!174 = !DILocation(line: 223, column: 6, scope: !68)
!175 = !DILocation(line: 224, column: 5, scope: !172)
!176 = !DILocation(line: 226, column: 11, scope: !68)
!177 = !DILocation(line: 226, column: 9, scope: !68)
!178 = !DILocation(line: 227, column: 25, scope: !179)
!179 = distinct !DILexicalBlock(scope: !68, file: !1, line: 227, column: 6)
!180 = !DILocation(line: 227, column: 22, scope: !179)
!181 = !DILocation(line: 227, column: 6, scope: !68)
!182 = !DILocation(line: 228, column: 5, scope: !179)
!183 = !DILocation(line: 230, column: 3, scope: !68)
!184 = !DILocation(line: 231, column: 14, scope: !68)
!185 = !DILocation(line: 231, column: 3, scope: !68)
!186 = !DILocation(line: 231, column: 24, scope: !68)
!187 = !DILocation(line: 231, column: 32, scope: !68)
!188 = !DILocation(line: 231, column: 35, scope: !68)
!189 = !DILocation(line: 232, column: 7, scope: !68)
!190 = !DILocation(line: 232, column: 16, scope: !68)
!191 = !DILocation(line: 232, column: 26, scope: !68)
!192 = !DILocation(line: 234, column: 12, scope: !193)
!193 = distinct !DILexicalBlock(scope: !68, file: !1, line: 234, column: 6)
!194 = !DILocation(line: 234, column: 6, scope: !193)
!195 = !DILocation(line: 234, column: 38, scope: !193)
!196 = !DILocation(line: 234, column: 6, scope: !68)
!197 = !DILocation(line: 235, column: 5, scope: !198)
!198 = distinct !DILexicalBlock(scope: !193, file: !1, line: 234, column: 43)
!199 = !DILocation(line: 239, column: 5, scope: !198)
!200 = !DILocation(line: 242, column: 34, scope: !68)
!201 = !DILocation(line: 242, column: 7, scope: !68)
!202 = !DILocation(line: 242, column: 5, scope: !68)
!203 = !DILocation(line: 243, column: 3, scope: !68)
!204 = !DILocation(line: 243, column: 16, scope: !68)
!205 = !DILocation(line: 243, column: 19, scope: !68)
!206 = !DILocation(line: 244, column: 18, scope: !68)
!207 = !DILocation(line: 244, column: 21, scope: !68)
!208 = !DILocation(line: 244, column: 33, scope: !68)
!209 = !DILocation(line: 244, column: 38, scope: !68)
!210 = !DILocation(line: 244, column: 43, scope: !68)
!211 = !DILocation(line: 244, column: 3, scope: !68)
!212 = !DILocation(line: 246, column: 3, scope: !68)
!213 = !DILocation(line: 247, column: 3, scope: !68)
!214 = !DILocation(line: 248, column: 1, scope: !68)
