; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/fileinfo.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_fileinfo = type { i8*, i32, i64, i32, i32, i32, i64, i64, %struct.anon, i32, i8*, i64, i64 }
%struct.anon = type { i8*, i8*, i8*, i8*, i8* }

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define %struct.curl_fileinfo* @Curl_fileinfo_alloc() #0 !dbg !16 {
entry:
  %retval = alloca %struct.curl_fileinfo*, align 8
  %tmp = alloca %struct.curl_fileinfo*, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_fileinfo** %tmp, metadata !65, metadata !66), !dbg !67
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !68
  %call = call i8* %0(i64 128), !dbg !68
  %1 = bitcast i8* %call to %struct.curl_fileinfo*, !dbg !68
  store %struct.curl_fileinfo* %1, %struct.curl_fileinfo** %tmp, align 8, !dbg !67
  %2 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %tmp, align 8, !dbg !69
  %tobool = icmp ne %struct.curl_fileinfo* %2, null, !dbg !69
  br i1 %tobool, label %if.end, label %if.then, !dbg !71

if.then:                                          ; preds = %entry
  store %struct.curl_fileinfo* null, %struct.curl_fileinfo** %retval, align 8, !dbg !72
  br label %return, !dbg !72

if.end:                                           ; preds = %entry
  %3 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %tmp, align 8, !dbg !73
  %4 = bitcast %struct.curl_fileinfo* %3 to i8*, !dbg !74
  call void @llvm.memset.p0i8.i64(i8* %4, i8 0, i64 128, i32 8, i1 false), !dbg !74
  %5 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %tmp, align 8, !dbg !75
  store %struct.curl_fileinfo* %5, %struct.curl_fileinfo** %retval, align 8, !dbg !76
  br label %return, !dbg !76

return:                                           ; preds = %if.end, %if.then
  %6 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %retval, align 8, !dbg !77
  ret %struct.curl_fileinfo* %6, !dbg !77
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define void @Curl_fileinfo_dtor(i8* %user, i8* %element) #0 !dbg !58 {
entry:
  %user.addr = alloca i8*, align 8
  %element.addr = alloca i8*, align 8
  %finfo = alloca %struct.curl_fileinfo*, align 8
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !78, metadata !66), !dbg !79
  store i8* %element, i8** %element.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %element.addr, metadata !80, metadata !66), !dbg !81
  call void @llvm.dbg.declare(metadata %struct.curl_fileinfo** %finfo, metadata !82, metadata !66), !dbg !83
  %0 = load i8*, i8** %element.addr, align 8, !dbg !84
  %1 = bitcast i8* %0 to %struct.curl_fileinfo*, !dbg !84
  store %struct.curl_fileinfo* %1, %struct.curl_fileinfo** %finfo, align 8, !dbg !83
  %2 = load i8*, i8** %user.addr, align 8, !dbg !85
  %3 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %finfo, align 8, !dbg !86
  %tobool = icmp ne %struct.curl_fileinfo* %3, null, !dbg !86
  br i1 %tobool, label %if.end, label %if.then, !dbg !88

if.then:                                          ; preds = %entry
  br label %return, !dbg !89

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !90

do.body:                                          ; preds = %if.end
  %4 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !91
  %5 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %finfo, align 8, !dbg !91
  %b_data = getelementptr inbounds %struct.curl_fileinfo, %struct.curl_fileinfo* %5, i32 0, i32 10, !dbg !91
  %6 = load i8*, i8** %b_data, align 8, !dbg !91
  call void %4(i8* %6), !dbg !91
  %7 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %finfo, align 8, !dbg !91
  %b_data1 = getelementptr inbounds %struct.curl_fileinfo, %struct.curl_fileinfo* %7, i32 0, i32 10, !dbg !91
  store i8* null, i8** %b_data1, align 8, !dbg !91
  br label %do.end, !dbg !91

do.end:                                           ; preds = %do.body
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !94
  %9 = load %struct.curl_fileinfo*, %struct.curl_fileinfo** %finfo, align 8, !dbg !94
  %10 = bitcast %struct.curl_fileinfo* %9 to i8*, !dbg !94
  call void %8(i8* %10), !dbg !94
  br label %return, !dbg !95

return:                                           ; preds = %do.end, %if.then
  ret void, !dbg !96
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!62, !63}
!llvm.ident = !{!64}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !15)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/fileinfo.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 231, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14}
!6 = !DIEnumerator(name: "CURLFILETYPE_FILE", value: 0)
!7 = !DIEnumerator(name: "CURLFILETYPE_DIRECTORY", value: 1)
!8 = !DIEnumerator(name: "CURLFILETYPE_SYMLINK", value: 2)
!9 = !DIEnumerator(name: "CURLFILETYPE_DEVICE_BLOCK", value: 3)
!10 = !DIEnumerator(name: "CURLFILETYPE_DEVICE_CHAR", value: 4)
!11 = !DIEnumerator(name: "CURLFILETYPE_NAMEDPIPE", value: 5)
!12 = !DIEnumerator(name: "CURLFILETYPE_SOCKET", value: 6)
!13 = !DIEnumerator(name: "CURLFILETYPE_DOOR", value: 7)
!14 = !DIEnumerator(name: "CURLFILETYPE_UNKNOWN", value: 8)
!15 = !{!16, !58}
!16 = distinct !DISubprogram(name: "Curl_fileinfo_alloc", scope: !1, file: !1, line: 31, type: !17, isLocal: false, isDefinition: true, scopeLine: 32, flags: DIFlagPrototyped, isOptimized: false, variables: !57)
!17 = !DISubroutineType(types: !18)
!18 = !{!19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_fileinfo", file: !4, line: 257, size: 1024, align: 64, elements: !21)
!21 = !{!22, !25, !27, !33, !35, !37, !38, !41, !42, !50, !51, !52, !56}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !20, file: !4, line: 258, baseType: !23, size: 64, align: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "filetype", scope: !20, file: !4, line: 259, baseType: !26, size: 32, align: 32, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlfiletype", file: !4, line: 242, baseType: !3)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !20, file: !4, line: 260, baseType: !28, size: 64, align: 64, offset: 128)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !29, line: 75, baseType: !30)
!29 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !31, line: 139, baseType: !32)
!31 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!32 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "perm", scope: !20, file: !4, line: 261, baseType: !34, size: 32, align: 32, offset: 192)
!34 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !20, file: !4, line: 262, baseType: !36, size: 32, align: 32, offset: 224)
!36 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !20, file: !4, line: 263, baseType: !36, size: 32, align: 32, offset: 256)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !20, file: !4, line: 264, baseType: !39, size: 64, align: 64, offset: 320)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !40, line: 216, baseType: !32)
!40 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!41 = !DIDerivedType(tag: DW_TAG_member, name: "hardlinks", scope: !20, file: !4, line: 265, baseType: !32, size: 64, align: 64, offset: 384)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "strings", scope: !20, file: !4, line: 274, baseType: !43, size: 320, align: 64, offset: 448)
!43 = !DICompositeType(tag: DW_TAG_structure_type, scope: !20, file: !4, line: 267, size: 320, align: 64, elements: !44)
!44 = !{!45, !46, !47, !48, !49}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !43, file: !4, line: 269, baseType: !23, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "perm", scope: !43, file: !4, line: 270, baseType: !23, size: 64, align: 64, offset: 64)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !43, file: !4, line: 271, baseType: !23, size: 64, align: 64, offset: 128)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "group", scope: !43, file: !4, line: 272, baseType: !23, size: 64, align: 64, offset: 192)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "target", scope: !43, file: !4, line: 273, baseType: !23, size: 64, align: 64, offset: 256)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !20, file: !4, line: 276, baseType: !34, size: 32, align: 32, offset: 768)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "b_data", scope: !20, file: !4, line: 279, baseType: !23, size: 64, align: 64, offset: 832)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "b_size", scope: !20, file: !4, line: 280, baseType: !53, size: 64, align: 64, offset: 896)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !54, line: 62, baseType: !55)
!54 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!55 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "b_used", scope: !20, file: !4, line: 281, baseType: !53, size: 64, align: 64, offset: 960)
!57 = !{}
!58 = distinct !DISubprogram(name: "Curl_fileinfo_dtor", scope: !1, file: !1, line: 40, type: !59, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !57)
!59 = !DISubroutineType(types: !60)
!60 = !{null, !61, !61}
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!62 = !{i32 2, !"Dwarf Version", i32 4}
!63 = !{i32 2, !"Debug Info Version", i32 3}
!64 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!65 = !DILocalVariable(name: "tmp", scope: !16, file: !1, line: 33, type: !19)
!66 = !DIExpression()
!67 = !DILocation(line: 33, column: 25, scope: !16)
!68 = !DILocation(line: 33, column: 31, scope: !16)
!69 = !DILocation(line: 34, column: 7, scope: !70)
!70 = distinct !DILexicalBlock(scope: !16, file: !1, line: 34, column: 6)
!71 = !DILocation(line: 34, column: 6, scope: !16)
!72 = !DILocation(line: 35, column: 5, scope: !70)
!73 = !DILocation(line: 36, column: 10, scope: !16)
!74 = !DILocation(line: 36, column: 3, scope: !16)
!75 = !DILocation(line: 37, column: 10, scope: !16)
!76 = !DILocation(line: 37, column: 3, scope: !16)
!77 = !DILocation(line: 38, column: 1, scope: !16)
!78 = !DILocalVariable(name: "user", arg: 1, scope: !58, file: !1, line: 40, type: !61)
!79 = !DILocation(line: 40, column: 31, scope: !58)
!80 = !DILocalVariable(name: "element", arg: 2, scope: !58, file: !1, line: 40, type: !61)
!81 = !DILocation(line: 40, column: 43, scope: !58)
!82 = !DILocalVariable(name: "finfo", scope: !58, file: !1, line: 42, type: !19)
!83 = !DILocation(line: 42, column: 25, scope: !58)
!84 = !DILocation(line: 42, column: 33, scope: !58)
!85 = !DILocation(line: 43, column: 10, scope: !58)
!86 = !DILocation(line: 44, column: 7, scope: !87)
!87 = distinct !DILexicalBlock(scope: !58, file: !1, line: 44, column: 6)
!88 = !DILocation(line: 44, column: 6, scope: !58)
!89 = !DILocation(line: 45, column: 5, scope: !87)
!90 = !DILocation(line: 47, column: 3, scope: !58)
!91 = !DILocation(line: 47, column: 3, scope: !92)
!92 = !DILexicalBlockFile(scope: !93, file: !1, discriminator: 1)
!93 = distinct !DILexicalBlock(scope: !58, file: !1, line: 47, column: 3)
!94 = !DILocation(line: 49, column: 3, scope: !58)
!95 = !DILocation(line: 50, column: 1, scope: !58)
!96 = !DILocation(line: 50, column: 1, scope: !97)
!97 = !DILexicalBlockFile(scope: !58, file: !1, discriminator: 1)
