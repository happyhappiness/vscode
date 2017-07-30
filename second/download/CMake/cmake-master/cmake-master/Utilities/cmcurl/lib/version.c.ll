; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/version.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_version_info_data = type { i32, i8*, i32, i8*, i32, i8*, i64, i8*, i8**, i8*, i32, i8*, i32, i8* }

@curl_version.initialized = internal global i8 0, align 1
@curl_version.version = internal global [200 x i8] zeroinitializer, align 16
@.str = private unnamed_addr constant [15 x i8] c"libcurl/7.54.0\00", align 1
@curl_version_info.initialized = internal global i8 0, align 1
@version_info = internal global %struct.curl_version_info_data { i32 3, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i32 472576, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i32 512, i8* null, i64 0, i8* null, i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @protocols, i32 0, i32 0), i8* null, i32 0, i8* null, i32 0, i8* null }, align 8
@.str.1 = private unnamed_addr constant [7 x i8] c"7.54.0\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"Linux\00", align 1
@protocols = internal constant [4 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8* null], align 16
@.str.3 = private unnamed_addr constant [5 x i8] c"file\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"ftp\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"http\00", align 1

; Function Attrs: nounwind uwtable
define void @Curl_version_init() #0 !dbg !12 {
entry:
  %call = call i8* @curl_version(), !dbg !66
  %call1 = call %struct.curl_version_info_data* @curl_version_info(i32 3), !dbg !67
  ret void, !dbg !68
}

; Function Attrs: nounwind uwtable
define i8* @curl_version() #0 !dbg !16 {
entry:
  %retval = alloca i8*, align 8
  %ptr = alloca i8*, align 8
  %len = alloca i64, align 8
  %left = alloca i64, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !69, metadata !70), !dbg !71
  store i8* getelementptr inbounds ([200 x i8], [200 x i8]* @curl_version.version, i32 0, i32 0), i8** %ptr, align 8, !dbg !71
  call void @llvm.dbg.declare(metadata i64* %len, metadata !72, metadata !70), !dbg !76
  call void @llvm.dbg.declare(metadata i64* %left, metadata !77, metadata !70), !dbg !78
  store i64 200, i64* %left, align 8, !dbg !78
  %0 = load i8, i8* @curl_version.initialized, align 1, !dbg !79
  %tobool = trunc i8 %0 to i1, !dbg !79
  br i1 %tobool, label %if.then, label %if.end, !dbg !81

if.then:                                          ; preds = %entry
  store i8* getelementptr inbounds ([200 x i8], [200 x i8]* @curl_version.version, i32 0, i32 0), i8** %retval, align 8, !dbg !82
  br label %return, !dbg !82

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %ptr, align 8, !dbg !83
  %call = call i8* @strcpy(i8* %1, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i32 0, i32 0)) #4, !dbg !84
  %2 = load i8*, i8** %ptr, align 8, !dbg !85
  %call1 = call i64 @strlen(i8* %2) #5, !dbg !86
  store i64 %call1, i64* %len, align 8, !dbg !87
  %3 = load i64, i64* %len, align 8, !dbg !88
  %4 = load i64, i64* %left, align 8, !dbg !89
  %sub = sub i64 %4, %3, !dbg !89
  store i64 %sub, i64* %left, align 8, !dbg !89
  %5 = load i64, i64* %len, align 8, !dbg !90
  %6 = load i8*, i8** %ptr, align 8, !dbg !91
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %5, !dbg !91
  store i8* %add.ptr, i8** %ptr, align 8, !dbg !91
  %7 = load i64, i64* %left, align 8, !dbg !92
  %cmp = icmp ugt i64 %7, 1, !dbg !94
  br i1 %cmp, label %if.then2, label %if.end8, !dbg !95

if.then2:                                         ; preds = %if.end
  store i64 0, i64* %len, align 8, !dbg !96
  %8 = load i64, i64* %len, align 8, !dbg !98
  %cmp3 = icmp ugt i64 %8, 0, !dbg !100
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !101

if.then4:                                         ; preds = %if.then2
  %9 = load i8*, i8** %ptr, align 8, !dbg !102
  store i8 32, i8* %9, align 1, !dbg !104
  %10 = load i64, i64* %len, align 8, !dbg !105
  %inc = add i64 %10, 1, !dbg !105
  store i64 %inc, i64* %len, align 8, !dbg !105
  %11 = load i64, i64* %left, align 8, !dbg !106
  %sub5 = sub i64 %11, %inc, !dbg !106
  store i64 %sub5, i64* %left, align 8, !dbg !106
  %12 = load i64, i64* %len, align 8, !dbg !107
  %13 = load i8*, i8** %ptr, align 8, !dbg !108
  %add.ptr6 = getelementptr inbounds i8, i8* %13, i64 %12, !dbg !108
  store i8* %add.ptr6, i8** %ptr, align 8, !dbg !108
  br label %if.end7, !dbg !109

if.end7:                                          ; preds = %if.then4, %if.then2
  br label %if.end8, !dbg !110

if.end8:                                          ; preds = %if.end7, %if.end
  store i8 1, i8* @curl_version.initialized, align 1, !dbg !111
  store i8* getelementptr inbounds ([200 x i8], [200 x i8]* @curl_version.version, i32 0, i32 0), i8** %retval, align 8, !dbg !112
  br label %return, !dbg !112

return:                                           ; preds = %if.end8, %if.then
  %14 = load i8*, i8** %retval, align 8, !dbg !113
  ret i8* %14, !dbg !113
}

; Function Attrs: nounwind uwtable
define %struct.curl_version_info_data* @curl_version_info(i32 %stamp) #0 !dbg !21 {
entry:
  %retval = alloca %struct.curl_version_info_data*, align 8
  %stamp.addr = alloca i32, align 4
  store i32 %stamp, i32* %stamp.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %stamp.addr, metadata !114, metadata !70), !dbg !115
  %0 = load i8, i8* @curl_version_info.initialized, align 1, !dbg !116
  %tobool = trunc i8 %0 to i1, !dbg !116
  br i1 %tobool, label %if.then, label %if.end, !dbg !118

if.then:                                          ; preds = %entry
  store %struct.curl_version_info_data* @version_info, %struct.curl_version_info_data** %retval, align 8, !dbg !119
  br label %return, !dbg !119

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %stamp.addr, align 4, !dbg !120
  store i8 1, i8* @curl_version_info.initialized, align 1, !dbg !121
  store %struct.curl_version_info_data* @version_info, %struct.curl_version_info_data** %retval, align 8, !dbg !122
  br label %return, !dbg !122

return:                                           ; preds = %if.end, %if.then
  %2 = load %struct.curl_version_info_data*, %struct.curl_version_info_data** %retval, align 8, !dbg !123
  ret %struct.curl_version_info_data* %2, !dbg !123
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!63, !64}
!llvm.ident = !{!65}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !11, globals: !50)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/version.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2403, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10}
!6 = !DIEnumerator(name: "CURLVERSION_FIRST", value: 0)
!7 = !DIEnumerator(name: "CURLVERSION_SECOND", value: 1)
!8 = !DIEnumerator(name: "CURLVERSION_THIRD", value: 2)
!9 = !DIEnumerator(name: "CURLVERSION_FOURTH", value: 3)
!10 = !DIEnumerator(name: "CURLVERSION_LAST", value: 4)
!11 = !{!12, !16, !21}
!12 = distinct !DISubprogram(name: "Curl_version_init", scope: !1, file: !1, line: 71, type: !13, isLocal: false, isDefinition: true, scopeLine: 72, flags: DIFlagPrototyped, isOptimized: false, variables: !15)
!13 = !DISubroutineType(types: !14)
!14 = !{null}
!15 = !{}
!16 = distinct !DISubprogram(name: "curl_version", scope: !1, file: !1, line: 77, type: !17, isLocal: false, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !15)
!17 = !DISubroutineType(types: !18)
!18 = !{!19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!21 = distinct !DISubprogram(name: "curl_version_info", scope: !1, file: !1, line: 342, type: !22, isLocal: false, isDefinition: true, scopeLine: 343, flags: DIFlagPrototyped, isOptimized: false, variables: !15)
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !29}
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_version_info_data", file: !4, line: 2444, baseType: !26)
!26 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 2418, size: 896, align: 64, elements: !27)
!27 = !{!28, !30, !33, !35, !36, !38, !39, !41, !42, !45, !46, !47, !48, !49}
!28 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !26, file: !4, line: 2419, baseType: !29, size: 32, align: 32)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLversion", file: !4, line: 2409, baseType: !3)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !26, file: !4, line: 2420, baseType: !31, size: 64, align: 64, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "version_num", scope: !26, file: !4, line: 2421, baseType: !34, size: 32, align: 32, offset: 128)
!34 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !26, file: !4, line: 2422, baseType: !31, size: 64, align: 64, offset: 192)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "features", scope: !26, file: !4, line: 2423, baseType: !37, size: 32, align: 32, offset: 256)
!37 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_version", scope: !26, file: !4, line: 2424, baseType: !31, size: 64, align: 64, offset: 320)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_version_num", scope: !26, file: !4, line: 2425, baseType: !40, size: 64, align: 64, offset: 384)
!40 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "libz_version", scope: !26, file: !4, line: 2426, baseType: !31, size: 64, align: 64, offset: 448)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "protocols", scope: !26, file: !4, line: 2428, baseType: !43, size: 64, align: 64, offset: 512)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "ares", scope: !26, file: !4, line: 2431, baseType: !31, size: 64, align: 64, offset: 576)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "ares_num", scope: !26, file: !4, line: 2432, baseType: !37, size: 32, align: 32, offset: 640)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "libidn", scope: !26, file: !4, line: 2435, baseType: !31, size: 64, align: 64, offset: 704)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "iconv_ver_num", scope: !26, file: !4, line: 2440, baseType: !37, size: 32, align: 32, offset: 768)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "libssh_version", scope: !26, file: !4, line: 2442, baseType: !31, size: 64, align: 64, offset: 832)
!50 = !{!51, !53, !57, !58, !59}
!51 = !DIGlobalVariable(name: "initialized", scope: !16, file: !1, line: 79, type: !52, isLocal: true, isDefinition: true, variable: i8* @curl_version.initialized)
!52 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!53 = !DIGlobalVariable(name: "version", scope: !16, file: !1, line: 80, type: !54, isLocal: true, isDefinition: true, variable: [200 x i8]* @curl_version.version)
!54 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 1600, align: 8, elements: !55)
!55 = !{!56}
!56 = !DISubrange(count: 200)
!57 = !DIGlobalVariable(name: "initialized", scope: !21, file: !1, line: 344, type: !52, isLocal: true, isDefinition: true, variable: i8* @curl_version_info.initialized)
!58 = !DIGlobalVariable(name: "version_info", scope: !0, file: !1, line: 265, type: !25, isLocal: true, isDefinition: true, variable: %struct.curl_version_info_data* @version_info)
!59 = !DIGlobalVariable(name: "protocols", scope: !0, file: !1, line: 187, type: !60, isLocal: true, isDefinition: true, variable: [4 x i8*]* @protocols)
!60 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 256, align: 64, elements: !61)
!61 = !{!62}
!62 = !DISubrange(count: 4)
!63 = !{i32 2, !"Dwarf Version", i32 4}
!64 = !{i32 2, !"Debug Info Version", i32 3}
!65 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!66 = !DILocation(line: 73, column: 3, scope: !12)
!67 = !DILocation(line: 74, column: 3, scope: !12)
!68 = !DILocation(line: 75, column: 1, scope: !12)
!69 = !DILocalVariable(name: "ptr", scope: !16, file: !1, line: 81, type: !19)
!70 = !DIExpression()
!71 = !DILocation(line: 81, column: 9, scope: !16)
!72 = !DILocalVariable(name: "len", scope: !16, file: !1, line: 82, type: !73)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !74, line: 62, baseType: !75)
!74 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!75 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!76 = !DILocation(line: 82, column: 10, scope: !16)
!77 = !DILocalVariable(name: "left", scope: !16, file: !1, line: 83, type: !73)
!78 = !DILocation(line: 83, column: 10, scope: !16)
!79 = !DILocation(line: 85, column: 6, scope: !80)
!80 = distinct !DILexicalBlock(scope: !16, file: !1, line: 85, column: 6)
!81 = !DILocation(line: 85, column: 6, scope: !16)
!82 = !DILocation(line: 86, column: 5, scope: !80)
!83 = !DILocation(line: 88, column: 10, scope: !16)
!84 = !DILocation(line: 88, column: 3, scope: !16)
!85 = !DILocation(line: 89, column: 16, scope: !16)
!86 = !DILocation(line: 89, column: 9, scope: !16)
!87 = !DILocation(line: 89, column: 7, scope: !16)
!88 = !DILocation(line: 90, column: 11, scope: !16)
!89 = !DILocation(line: 90, column: 8, scope: !16)
!90 = !DILocation(line: 91, column: 10, scope: !16)
!91 = !DILocation(line: 91, column: 7, scope: !16)
!92 = !DILocation(line: 93, column: 6, scope: !93)
!93 = distinct !DILexicalBlock(scope: !16, file: !1, line: 93, column: 6)
!94 = !DILocation(line: 93, column: 11, scope: !93)
!95 = !DILocation(line: 93, column: 6, scope: !16)
!96 = !DILocation(line: 94, column: 9, scope: !97)
!97 = distinct !DILexicalBlock(scope: !93, file: !1, line: 93, column: 16)
!98 = !DILocation(line: 96, column: 8, scope: !99)
!99 = distinct !DILexicalBlock(scope: !97, file: !1, line: 96, column: 8)
!100 = !DILocation(line: 96, column: 12, scope: !99)
!101 = !DILocation(line: 96, column: 8, scope: !97)
!102 = !DILocation(line: 97, column: 8, scope: !103)
!103 = distinct !DILexicalBlock(scope: !99, file: !1, line: 96, column: 17)
!104 = !DILocation(line: 97, column: 12, scope: !103)
!105 = !DILocation(line: 98, column: 15, scope: !103)
!106 = !DILocation(line: 98, column: 12, scope: !103)
!107 = !DILocation(line: 99, column: 14, scope: !103)
!108 = !DILocation(line: 99, column: 11, scope: !103)
!109 = !DILocation(line: 100, column: 5, scope: !103)
!110 = !DILocation(line: 101, column: 3, scope: !97)
!111 = !DILocation(line: 177, column: 15, scope: !16)
!112 = !DILocation(line: 178, column: 3, scope: !16)
!113 = !DILocation(line: 179, column: 1, scope: !16)
!114 = !DILocalVariable(name: "stamp", arg: 1, scope: !21, file: !1, line: 342, type: !29)
!115 = !DILocation(line: 342, column: 55, scope: !21)
!116 = !DILocation(line: 352, column: 6, scope: !117)
!117 = distinct !DILexicalBlock(scope: !21, file: !1, line: 352, column: 6)
!118 = !DILocation(line: 352, column: 6, scope: !21)
!119 = !DILocation(line: 353, column: 5, scope: !117)
!120 = !DILocation(line: 395, column: 9, scope: !21)
!121 = !DILocation(line: 397, column: 15, scope: !21)
!122 = !DILocation(line: 398, column: 3, scope: !21)
!123 = !DILocation(line: 399, column: 1, scope: !21)
