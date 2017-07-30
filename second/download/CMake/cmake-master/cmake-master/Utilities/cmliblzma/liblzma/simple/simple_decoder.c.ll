; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_options_bcj = type { i32 }

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_props_decode(i8** %options, %struct.lzma_allocator* %allocator, i8* %props, i64 %props_size) #0 !dbg !26 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8**, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %props.addr = alloca i8*, align 8
  %props_size.addr = alloca i64, align 8
  %opt = alloca %struct.lzma_options_bcj*, align 8
  store i8** %options, i8*** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %options.addr, metadata !59, metadata !60), !dbg !61
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !62, metadata !60), !dbg !63
  store i8* %props, i8** %props.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %props.addr, metadata !64, metadata !60), !dbg !65
  store i64 %props_size, i64* %props_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %props_size.addr, metadata !66, metadata !60), !dbg !67
  call void @llvm.dbg.declare(metadata %struct.lzma_options_bcj** %opt, metadata !68, metadata !60), !dbg !75
  %0 = load i64, i64* %props_size.addr, align 8, !dbg !76
  %cmp = icmp eq i64 %0, 0, !dbg !78
  br i1 %cmp, label %if.then, label %if.end, !dbg !79

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !80
  br label %return, !dbg !80

if.end:                                           ; preds = %entry
  %1 = load i64, i64* %props_size.addr, align 8, !dbg !81
  %cmp1 = icmp ne i64 %1, 4, !dbg !83
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !84

if.then2:                                         ; preds = %if.end
  store i32 8, i32* %retval, align 4, !dbg !85
  br label %return, !dbg !85

if.end3:                                          ; preds = %if.end
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !86
  %call = call noalias i8* @lzma_alloc(i64 4, %struct.lzma_allocator* %2), !dbg !87
  %3 = bitcast i8* %call to %struct.lzma_options_bcj*, !dbg !87
  store %struct.lzma_options_bcj* %3, %struct.lzma_options_bcj** %opt, align 8, !dbg !88
  %4 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !89
  %cmp4 = icmp eq %struct.lzma_options_bcj* %4, null, !dbg !91
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !92

if.then5:                                         ; preds = %if.end3
  store i32 5, i32* %retval, align 4, !dbg !93
  br label %return, !dbg !93

if.end6:                                          ; preds = %if.end3
  %5 = load i8*, i8** %props.addr, align 8, !dbg !94
  %call7 = call i32 @read32le(i8* %5), !dbg !95
  %6 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !96
  %start_offset = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %6, i32 0, i32 0, !dbg !97
  store i32 %call7, i32* %start_offset, align 4, !dbg !98
  %7 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !99
  %start_offset8 = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %7, i32 0, i32 0, !dbg !101
  %8 = load i32, i32* %start_offset8, align 4, !dbg !101
  %cmp9 = icmp eq i32 %8, 0, !dbg !102
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !103

if.then10:                                        ; preds = %if.end6
  %9 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !104
  %10 = bitcast %struct.lzma_options_bcj* %9 to i8*, !dbg !104
  %11 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !105
  call void @lzma_free(i8* %10, %struct.lzma_allocator* %11), !dbg !106
  br label %if.end11, !dbg !106

if.else:                                          ; preds = %if.end6
  %12 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !107
  %13 = bitcast %struct.lzma_options_bcj* %12 to i8*, !dbg !107
  %14 = load i8**, i8*** %options.addr, align 8, !dbg !108
  store i8* %13, i8** %14, align 8, !dbg !109
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then10
  store i32 0, i32* %retval, align 4, !dbg !110
  br label %return, !dbg !110

return:                                           ; preds = %if.end11, %if.then5, %if.then2, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !111
  ret i32 %15, !dbg !111
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @read32le(i8* %buf) #3 !dbg !52 {
entry:
  %buf.addr = alloca i8*, align 8
  %num = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !112, metadata !60), !dbg !113
  call void @llvm.dbg.declare(metadata i32* %num, metadata !114, metadata !60), !dbg !115
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !116
  %1 = bitcast i8* %0 to i32*, !dbg !117
  %2 = load i32, i32* %1, align 4, !dbg !117
  store i32 %2, i32* %num, align 4, !dbg !115
  %3 = load i32, i32* %num, align 4, !dbg !118
  ret i32 %3, !dbg !119
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!56, !57}
!llvm.ident = !{!58}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !25)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !{!19, !20, !22}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !23, line: 51, baseType: !24)
!23 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!24 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!25 = !{!26, !52}
!26 = distinct !DISubprogram(name: "lzma_simple_props_decode", scope: !1, file: !1, line: 17, type: !27, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !51)
!27 = !DISubroutineType(types: !28)
!28 = !{!29, !30, !31, !47, !39}
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !33)
!33 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !34)
!34 = !{!35, !42, !46}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !33, file: !4, line: 376, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DISubroutineType(types: !38)
!38 = !{!19, !19, !39, !39}
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !40, line: 62, baseType: !41)
!40 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!41 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !33, file: !4, line: 390, baseType: !43, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DISubroutineType(types: !45)
!45 = !{null, !19, !19}
!46 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !33, file: !4, line: 401, baseType: !19, size: 64, align: 64, offset: 128)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !23, line: 48, baseType: !50)
!50 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!51 = !{}
!52 = distinct !DISubprogram(name: "read32le", scope: !53, file: !53, line: 209, type: !54, isLocal: true, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !51)
!53 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DISubroutineType(types: !55)
!55 = !{!22, !47}
!56 = !{i32 2, !"Dwarf Version", i32 4}
!57 = !{i32 2, !"Debug Info Version", i32 3}
!58 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!59 = !DILocalVariable(name: "options", arg: 1, scope: !26, file: !1, line: 17, type: !30)
!60 = !DIExpression()
!61 = !DILocation(line: 17, column: 33, scope: !26)
!62 = !DILocalVariable(name: "allocator", arg: 2, scope: !26, file: !1, line: 17, type: !31)
!63 = !DILocation(line: 17, column: 58, scope: !26)
!64 = !DILocalVariable(name: "props", arg: 3, scope: !26, file: !1, line: 18, type: !47)
!65 = !DILocation(line: 18, column: 18, scope: !26)
!66 = !DILocalVariable(name: "props_size", arg: 4, scope: !26, file: !1, line: 18, type: !39)
!67 = !DILocation(line: 18, column: 32, scope: !26)
!68 = !DILocalVariable(name: "opt", scope: !26, file: !1, line: 20, type: !69)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_bcj", file: !71, line: 90, baseType: !72)
!71 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/bcj.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!72 = !DICompositeType(tag: DW_TAG_structure_type, file: !71, line: 73, size: 32, align: 32, elements: !73)
!73 = !{!74}
!74 = !DIDerivedType(tag: DW_TAG_member, name: "start_offset", scope: !72, file: !71, line: 88, baseType: !22, size: 32, align: 32)
!75 = !DILocation(line: 20, column: 20, scope: !26)
!76 = !DILocation(line: 22, column: 6, scope: !77)
!77 = distinct !DILexicalBlock(scope: !26, file: !1, line: 22, column: 6)
!78 = !DILocation(line: 22, column: 17, scope: !77)
!79 = !DILocation(line: 22, column: 6, scope: !26)
!80 = !DILocation(line: 23, column: 3, scope: !77)
!81 = !DILocation(line: 25, column: 6, scope: !82)
!82 = distinct !DILexicalBlock(scope: !26, file: !1, line: 25, column: 6)
!83 = !DILocation(line: 25, column: 17, scope: !82)
!84 = !DILocation(line: 25, column: 6, scope: !26)
!85 = !DILocation(line: 26, column: 3, scope: !82)
!86 = !DILocation(line: 28, column: 45, scope: !26)
!87 = !DILocation(line: 28, column: 8, scope: !26)
!88 = !DILocation(line: 28, column: 6, scope: !26)
!89 = !DILocation(line: 29, column: 6, scope: !90)
!90 = distinct !DILexicalBlock(scope: !26, file: !1, line: 29, column: 6)
!91 = !DILocation(line: 29, column: 10, scope: !90)
!92 = !DILocation(line: 29, column: 6, scope: !26)
!93 = !DILocation(line: 30, column: 3, scope: !90)
!94 = !DILocation(line: 32, column: 41, scope: !26)
!95 = !DILocation(line: 32, column: 22, scope: !26)
!96 = !DILocation(line: 32, column: 2, scope: !26)
!97 = !DILocation(line: 32, column: 7, scope: !26)
!98 = !DILocation(line: 32, column: 20, scope: !26)
!99 = !DILocation(line: 35, column: 6, scope: !100)
!100 = distinct !DILexicalBlock(scope: !26, file: !1, line: 35, column: 6)
!101 = !DILocation(line: 35, column: 11, scope: !100)
!102 = !DILocation(line: 35, column: 24, scope: !100)
!103 = !DILocation(line: 35, column: 6, scope: !26)
!104 = !DILocation(line: 36, column: 13, scope: !100)
!105 = !DILocation(line: 36, column: 18, scope: !100)
!106 = !DILocation(line: 36, column: 3, scope: !100)
!107 = !DILocation(line: 38, column: 14, scope: !100)
!108 = !DILocation(line: 38, column: 4, scope: !100)
!109 = !DILocation(line: 38, column: 12, scope: !100)
!110 = !DILocation(line: 40, column: 2, scope: !26)
!111 = !DILocation(line: 41, column: 1, scope: !26)
!112 = !DILocalVariable(name: "buf", arg: 1, scope: !52, file: !53, line: 209, type: !47)
!113 = !DILocation(line: 209, column: 25, scope: !52)
!114 = !DILocalVariable(name: "num", scope: !52, file: !53, line: 211, type: !22)
!115 = !DILocation(line: 211, column: 11, scope: !52)
!116 = !DILocation(line: 211, column: 36, scope: !52)
!117 = !DILocation(line: 211, column: 17, scope: !52)
!118 = !DILocation(line: 212, column: 9, scope: !52)
!119 = !DILocation(line: 212, column: 2, scope: !52)
