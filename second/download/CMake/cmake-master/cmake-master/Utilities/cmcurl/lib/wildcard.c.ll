; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.WildcardData = type { i32, i8*, i8*, %struct.curl_llist, i8*, void (i8*)*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }

@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define i32 @Curl_wildcard_init(%struct.WildcardData* %wc) #0 !dbg !114 {
entry:
  %wc.addr = alloca %struct.WildcardData*, align 8
  store %struct.WildcardData* %wc, %struct.WildcardData** %wc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.WildcardData** %wc.addr, metadata !162, metadata !163), !dbg !164
  %0 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !165
  %filelist = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %0, i32 0, i32 3, !dbg !166
  call void @Curl_llist_init(%struct.curl_llist* %filelist, void (i8*, i8*)* @Curl_fileinfo_dtor), !dbg !167
  %1 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !168
  %state = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %1, i32 0, i32 0, !dbg !169
  store i32 1, i32* %state, align 8, !dbg !170
  ret i32 0, !dbg !171
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @Curl_llist_init(%struct.curl_llist*, void (i8*, i8*)*) #2

declare void @Curl_fileinfo_dtor(i8*, i8*) #2

; Function Attrs: nounwind uwtable
define void @Curl_wildcard_dtor(%struct.WildcardData* %wc) #0 !dbg !156 {
entry:
  %wc.addr = alloca %struct.WildcardData*, align 8
  store %struct.WildcardData* %wc, %struct.WildcardData** %wc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.WildcardData** %wc.addr, metadata !172, metadata !163), !dbg !173
  %0 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !174
  %tobool = icmp ne %struct.WildcardData* %0, null, !dbg !174
  br i1 %tobool, label %if.end, label %if.then, !dbg !176

if.then:                                          ; preds = %entry
  br label %return, !dbg !177

if.end:                                           ; preds = %entry
  %1 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !178
  %tmp_dtor = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %1, i32 0, i32 5, !dbg !180
  %2 = load void (i8*)*, void (i8*)** %tmp_dtor, align 8, !dbg !180
  %tobool1 = icmp ne void (i8*)* %2, null, !dbg !178
  br i1 %tobool1, label %if.then2, label %if.end6, !dbg !181

if.then2:                                         ; preds = %if.end
  %3 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !182
  %tmp_dtor3 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %3, i32 0, i32 5, !dbg !184
  %4 = load void (i8*)*, void (i8*)** %tmp_dtor3, align 8, !dbg !184
  %5 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !185
  %tmp = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %5, i32 0, i32 4, !dbg !186
  %6 = load i8*, i8** %tmp, align 8, !dbg !186
  call void %4(i8* %6), !dbg !182
  %7 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !187
  %tmp_dtor4 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %7, i32 0, i32 5, !dbg !188
  store void (i8*)* null, void (i8*)** %tmp_dtor4, align 8, !dbg !189
  %8 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !190
  %tmp5 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %8, i32 0, i32 4, !dbg !191
  store i8* null, i8** %tmp5, align 8, !dbg !192
  br label %if.end6, !dbg !193

if.end6:                                          ; preds = %if.then2, %if.end
  br label %do.body, !dbg !194

do.body:                                          ; preds = %if.end6
  br label %do.end, !dbg !195

do.end:                                           ; preds = %do.body
  %9 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !198
  %filelist = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %9, i32 0, i32 3, !dbg !199
  call void @Curl_llist_destroy(%struct.curl_llist* %filelist, i8* null), !dbg !200
  %10 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !201
  %11 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !201
  %path = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %11, i32 0, i32 1, !dbg !201
  %12 = load i8*, i8** %path, align 8, !dbg !201
  call void %10(i8* %12), !dbg !201
  %13 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !202
  %path7 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %13, i32 0, i32 1, !dbg !203
  store i8* null, i8** %path7, align 8, !dbg !204
  %14 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !205
  %15 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !205
  %pattern = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %15, i32 0, i32 2, !dbg !205
  %16 = load i8*, i8** %pattern, align 8, !dbg !205
  call void %14(i8* %16), !dbg !205
  %17 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !206
  %pattern8 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %17, i32 0, i32 2, !dbg !207
  store i8* null, i8** %pattern8, align 8, !dbg !208
  %18 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !209
  %customptr = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %18, i32 0, i32 6, !dbg !210
  store i8* null, i8** %customptr, align 8, !dbg !211
  %19 = load %struct.WildcardData*, %struct.WildcardData** %wc.addr, align 8, !dbg !212
  %state = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %19, i32 0, i32 0, !dbg !213
  store i32 1, i32* %state, align 8, !dbg !214
  br label %return, !dbg !215

return:                                           ; preds = %do.end, %if.then
  ret void, !dbg !216
}

declare void @Curl_llist_destroy(%struct.curl_llist*, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!159, !160}
!llvm.ident = !{!161}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !111, subprograms: !113)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 434, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99}
!6 = !DIEnumerator(name: "CURLE_OK", value: 0)
!7 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!8 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!9 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!10 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!11 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!12 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!13 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!15 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!16 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!17 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!18 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!19 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!20 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!21 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!22 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!23 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!24 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!25 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!26 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!27 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!28 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!29 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!30 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!31 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!32 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!33 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!34 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!35 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!36 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!37 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!38 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!39 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!40 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!41 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!42 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!43 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!44 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!45 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!47 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!48 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!49 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!51 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!52 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!53 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!54 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!55 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!56 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!57 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!58 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!59 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!60 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!61 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!62 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!63 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!64 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!65 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!66 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!67 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!68 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!69 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!70 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!71 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!72 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!73 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!74 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!75 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!76 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!77 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!78 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!79 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!80 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!81 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!82 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!83 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!84 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!85 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!86 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!87 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!88 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!89 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!90 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!91 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!92 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!93 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!94 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!95 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!96 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!97 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!98 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!99 = !DIEnumerator(name: "CURL_LAST", value: 93)
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !101, line: 30, size: 32, align: 32, elements: !102)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!102 = !{!103, !104, !105, !106, !107, !108, !109, !110}
!103 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!104 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!105 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!106 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!107 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!108 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!109 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!110 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!111 = !{!112}
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!113 = !{!114, !156}
!114 = distinct !DISubprogram(name: "Curl_wildcard_init", scope: !1, file: !1, line: 33, type: !115, isLocal: false, isDefinition: true, scopeLine: 34, flags: DIFlagPrototyped, isOptimized: false, variables: !155)
!115 = !DISubroutineType(types: !116)
!116 = !{!117, !118}
!117 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !119, size: 64, align: 64)
!119 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !101, line: 46, size: 640, align: 64, elements: !120)
!120 = !{!121, !123, !126, !127, !148, !149, !154}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !119, file: !101, line: 47, baseType: !122, size: 32, align: 32)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !101, line: 41, baseType: !100)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !119, file: !101, line: 48, baseType: !124, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !119, file: !101, line: 49, baseType: !124, size: 64, align: 64, offset: 128)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !119, file: !101, line: 50, baseType: !128, size: 256, align: 64, offset: 192)
!128 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !129, line: 37, size: 256, align: 64, elements: !130)
!129 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!130 = !{!131, !138, !139, !144}
!131 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !128, file: !129, line: 38, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !129, line: 30, size: 192, align: 64, elements: !134)
!134 = !{!135, !136, !137}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !133, file: !129, line: 31, baseType: !112, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !133, file: !129, line: 33, baseType: !132, size: 64, align: 64, offset: 64)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !133, file: !129, line: 34, baseType: !132, size: 64, align: 64, offset: 128)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !128, file: !129, line: 39, baseType: !132, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !128, file: !129, line: 41, baseType: !140, size: 64, align: 64, offset: 128)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !129, line: 28, baseType: !141)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DISubroutineType(types: !143)
!143 = !{null, !112, !112}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !128, file: !129, line: 43, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !146, line: 62, baseType: !147)
!146 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!147 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !119, file: !101, line: 51, baseType: !112, size: 64, align: 64, offset: 448)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !119, file: !101, line: 52, baseType: !150, size: 64, align: 64, offset: 512)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !101, line: 43, baseType: !151)
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!152 = !DISubroutineType(types: !153)
!153 = !{null, !112}
!154 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !119, file: !101, line: 53, baseType: !112, size: 64, align: 64, offset: 576)
!155 = !{}
!156 = distinct !DISubprogram(name: "Curl_wildcard_dtor", scope: !1, file: !1, line: 41, type: !157, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !155)
!157 = !DISubroutineType(types: !158)
!158 = !{null, !118}
!159 = !{i32 2, !"Dwarf Version", i32 4}
!160 = !{i32 2, !"Debug Info Version", i32 3}
!161 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!162 = !DILocalVariable(name: "wc", arg: 1, scope: !114, file: !1, line: 33, type: !118)
!163 = !DIExpression()
!164 = !DILocation(line: 33, column: 50, scope: !114)
!165 = !DILocation(line: 35, column: 20, scope: !114)
!166 = !DILocation(line: 35, column: 24, scope: !114)
!167 = !DILocation(line: 35, column: 3, scope: !114)
!168 = !DILocation(line: 36, column: 3, scope: !114)
!169 = !DILocation(line: 36, column: 7, scope: !114)
!170 = !DILocation(line: 36, column: 13, scope: !114)
!171 = !DILocation(line: 38, column: 3, scope: !114)
!172 = !DILocalVariable(name: "wc", arg: 1, scope: !156, file: !1, line: 41, type: !118)
!173 = !DILocation(line: 41, column: 46, scope: !156)
!174 = !DILocation(line: 43, column: 7, scope: !175)
!175 = distinct !DILexicalBlock(scope: !156, file: !1, line: 43, column: 6)
!176 = !DILocation(line: 43, column: 6, scope: !156)
!177 = !DILocation(line: 44, column: 5, scope: !175)
!178 = !DILocation(line: 46, column: 6, scope: !179)
!179 = distinct !DILexicalBlock(scope: !156, file: !1, line: 46, column: 6)
!180 = !DILocation(line: 46, column: 10, scope: !179)
!181 = !DILocation(line: 46, column: 6, scope: !156)
!182 = !DILocation(line: 47, column: 5, scope: !183)
!183 = distinct !DILexicalBlock(scope: !179, file: !1, line: 46, column: 20)
!184 = !DILocation(line: 47, column: 9, scope: !183)
!185 = !DILocation(line: 47, column: 18, scope: !183)
!186 = !DILocation(line: 47, column: 22, scope: !183)
!187 = !DILocation(line: 48, column: 5, scope: !183)
!188 = !DILocation(line: 48, column: 9, scope: !183)
!189 = !DILocation(line: 48, column: 18, scope: !183)
!190 = !DILocation(line: 49, column: 5, scope: !183)
!191 = !DILocation(line: 49, column: 9, scope: !183)
!192 = !DILocation(line: 49, column: 13, scope: !183)
!193 = !DILocation(line: 50, column: 3, scope: !183)
!194 = !DILocation(line: 51, column: 3, scope: !156)
!195 = !DILocation(line: 51, column: 3, scope: !196)
!196 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!197 = distinct !DILexicalBlock(scope: !156, file: !1, line: 51, column: 3)
!198 = !DILocation(line: 53, column: 23, scope: !156)
!199 = !DILocation(line: 53, column: 27, scope: !156)
!200 = !DILocation(line: 53, column: 3, scope: !156)
!201 = !DILocation(line: 56, column: 3, scope: !156)
!202 = !DILocation(line: 57, column: 3, scope: !156)
!203 = !DILocation(line: 57, column: 7, scope: !156)
!204 = !DILocation(line: 57, column: 12, scope: !156)
!205 = !DILocation(line: 58, column: 3, scope: !156)
!206 = !DILocation(line: 59, column: 3, scope: !156)
!207 = !DILocation(line: 59, column: 7, scope: !156)
!208 = !DILocation(line: 59, column: 15, scope: !156)
!209 = !DILocation(line: 61, column: 3, scope: !156)
!210 = !DILocation(line: 61, column: 7, scope: !156)
!211 = !DILocation(line: 61, column: 17, scope: !156)
!212 = !DILocation(line: 62, column: 3, scope: !156)
!213 = !DILocation(line: 62, column: 7, scope: !156)
!214 = !DILocation(line: 62, column: 13, scope: !156)
!215 = !DILocation(line: 63, column: 1, scope: !156)
!216 = !DILocation(line: 63, column: 1, scope: !217)
!217 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 1)
