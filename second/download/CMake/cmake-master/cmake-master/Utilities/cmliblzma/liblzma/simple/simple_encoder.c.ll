; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_options_bcj = type { i32 }

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_props_size(i32* %size, i8* %options) #0 !dbg !25 {
entry:
  %size.addr = alloca i32*, align 8
  %options.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_bcj*, align 8
  store i32* %size, i32** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %size.addr, metadata !45, metadata !46), !dbg !47
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !48, metadata !46), !dbg !49
  call void @llvm.dbg.declare(metadata %struct.lzma_options_bcj** %opt, metadata !50, metadata !46), !dbg !59
  %0 = load i8*, i8** %options.addr, align 8, !dbg !60
  %1 = bitcast i8* %0 to %struct.lzma_options_bcj*, !dbg !60
  store %struct.lzma_options_bcj* %1, %struct.lzma_options_bcj** %opt, align 8, !dbg !59
  %2 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !61
  %cmp = icmp eq %struct.lzma_options_bcj* %2, null, !dbg !62
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !63

lor.rhs:                                          ; preds = %entry
  %3 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !64
  %start_offset = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %3, i32 0, i32 0, !dbg !66
  %4 = load i32, i32* %start_offset, align 4, !dbg !66
  %cmp1 = icmp eq i32 %4, 0, !dbg !67
  br label %lor.end, !dbg !68

lor.end:                                          ; preds = %lor.rhs, %entry
  %5 = phi i1 [ true, %entry ], [ %cmp1, %lor.rhs ]
  %cond = select i1 %5, i32 0, i32 4, !dbg !69
  %6 = load i32*, i32** %size.addr, align 8, !dbg !71
  store i32 %cond, i32* %6, align 4, !dbg !72
  ret i32 0, !dbg !73
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_props_encode(i8* %options, i8* %out) #0 !dbg !32 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_bcj*, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !74, metadata !46), !dbg !75
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !76, metadata !46), !dbg !77
  call void @llvm.dbg.declare(metadata %struct.lzma_options_bcj** %opt, metadata !78, metadata !46), !dbg !79
  %0 = load i8*, i8** %options.addr, align 8, !dbg !80
  %1 = bitcast i8* %0 to %struct.lzma_options_bcj*, !dbg !80
  store %struct.lzma_options_bcj* %1, %struct.lzma_options_bcj** %opt, align 8, !dbg !79
  %2 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !81
  %cmp = icmp eq %struct.lzma_options_bcj* %2, null, !dbg !83
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !84

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !85
  %start_offset = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %3, i32 0, i32 0, !dbg !87
  %4 = load i32, i32* %start_offset, align 4, !dbg !87
  %cmp1 = icmp eq i32 %4, 0, !dbg !88
  br i1 %cmp1, label %if.then, label %if.end, !dbg !89

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !90
  br label %return, !dbg !90

if.end:                                           ; preds = %lor.lhs.false
  %5 = load i8*, i8** %out.addr, align 8, !dbg !91
  %6 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %opt, align 8, !dbg !91
  %start_offset2 = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %6, i32 0, i32 0, !dbg !91
  %7 = load i32, i32* %start_offset2, align 4, !dbg !91
  call void @write32ne(i8* %5, i32 %7), !dbg !91
  store i32 0, i32* %retval, align 4, !dbg !92
  br label %return, !dbg !92

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !93
  ret i32 %8, !dbg !93
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @write32ne(i8* %buf, i32 %num) #2 !dbg !38 {
entry:
  %buf.addr = alloca i8*, align 8
  %num.addr = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !94, metadata !46), !dbg !95
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !96, metadata !46), !dbg !97
  %0 = load i32, i32* %num.addr, align 4, !dbg !98
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !99
  %2 = bitcast i8* %1 to i32*, !dbg !100
  store i32 %0, i32* %2, align 4, !dbg !101
  ret void, !dbg !102
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!42, !43}
!llvm.ident = !{!44}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !24)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!18 = !{!19, !20, !23}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !21, line: 51, baseType: !22)
!21 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!22 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!24 = !{!25, !32, !38}
!25 = distinct !DISubprogram(name: "lzma_simple_props_size", scope: !1, file: !1, line: 17, type: !26, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !31)
!26 = !DISubroutineType(types: !27)
!27 = !{!28, !23, !29}
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!31 = !{}
!32 = distinct !DISubprogram(name: "lzma_simple_props_encode", scope: !1, file: !1, line: 26, type: !33, isLocal: false, isDefinition: true, scopeLine: 27, flags: DIFlagPrototyped, isOptimized: false, variables: !31)
!33 = !DISubroutineType(types: !34)
!34 = !{!28, !29, !35}
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !21, line: 48, baseType: !37)
!37 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!38 = distinct !DISubprogram(name: "write32ne", scope: !39, file: !39, line: 255, type: !40, isLocal: true, isDefinition: true, scopeLine: 256, flags: DIFlagPrototyped, isOptimized: false, variables: !31)
!39 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!40 = !DISubroutineType(types: !41)
!41 = !{null, !35, !20}
!42 = !{i32 2, !"Dwarf Version", i32 4}
!43 = !{i32 2, !"Debug Info Version", i32 3}
!44 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!45 = !DILocalVariable(name: "size", arg: 1, scope: !25, file: !1, line: 17, type: !23)
!46 = !DIExpression()
!47 = !DILocation(line: 17, column: 34, scope: !25)
!48 = !DILocalVariable(name: "options", arg: 2, scope: !25, file: !1, line: 17, type: !29)
!49 = !DILocation(line: 17, column: 52, scope: !25)
!50 = !DILocalVariable(name: "opt", scope: !25, file: !1, line: 19, type: !51)
!51 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !52)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !54)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_bcj", file: !55, line: 90, baseType: !56)
!55 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/bcj.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!56 = !DICompositeType(tag: DW_TAG_structure_type, file: !55, line: 73, size: 32, align: 32, elements: !57)
!57 = !{!58}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "start_offset", scope: !56, file: !55, line: 88, baseType: !20, size: 32, align: 32)
!59 = !DILocation(line: 19, column: 32, scope: !25)
!60 = !DILocation(line: 19, column: 38, scope: !25)
!61 = !DILocation(line: 20, column: 11, scope: !25)
!62 = !DILocation(line: 20, column: 15, scope: !25)
!63 = !DILocation(line: 20, column: 23, scope: !25)
!64 = !DILocation(line: 20, column: 26, scope: !65)
!65 = !DILexicalBlockFile(scope: !25, file: !1, discriminator: 1)
!66 = !DILocation(line: 20, column: 31, scope: !65)
!67 = !DILocation(line: 20, column: 44, scope: !65)
!68 = !DILocation(line: 20, column: 23, scope: !65)
!69 = !DILocation(line: 20, column: 10, scope: !70)
!70 = !DILexicalBlockFile(scope: !25, file: !1, discriminator: 2)
!71 = !DILocation(line: 20, column: 3, scope: !70)
!72 = !DILocation(line: 20, column: 8, scope: !70)
!73 = !DILocation(line: 21, column: 2, scope: !25)
!74 = !DILocalVariable(name: "options", arg: 1, scope: !32, file: !1, line: 26, type: !29)
!75 = !DILocation(line: 26, column: 38, scope: !32)
!76 = !DILocalVariable(name: "out", arg: 2, scope: !32, file: !1, line: 26, type: !35)
!77 = !DILocation(line: 26, column: 56, scope: !32)
!78 = !DILocalVariable(name: "opt", scope: !32, file: !1, line: 28, type: !51)
!79 = !DILocation(line: 28, column: 32, scope: !32)
!80 = !DILocation(line: 28, column: 38, scope: !32)
!81 = !DILocation(line: 32, column: 6, scope: !82)
!82 = distinct !DILexicalBlock(scope: !32, file: !1, line: 32, column: 6)
!83 = !DILocation(line: 32, column: 10, scope: !82)
!84 = !DILocation(line: 32, column: 18, scope: !82)
!85 = !DILocation(line: 32, column: 21, scope: !86)
!86 = !DILexicalBlockFile(scope: !82, file: !1, discriminator: 1)
!87 = !DILocation(line: 32, column: 26, scope: !86)
!88 = !DILocation(line: 32, column: 39, scope: !86)
!89 = !DILocation(line: 32, column: 6, scope: !86)
!90 = !DILocation(line: 33, column: 3, scope: !82)
!91 = !DILocation(line: 35, column: 2, scope: !32)
!92 = !DILocation(line: 37, column: 2, scope: !32)
!93 = !DILocation(line: 38, column: 1, scope: !32)
!94 = !DILocalVariable(name: "buf", arg: 1, scope: !38, file: !39, line: 255, type: !35)
!95 = !DILocation(line: 255, column: 20, scope: !38)
!96 = !DILocalVariable(name: "num", arg: 2, scope: !38, file: !39, line: 255, type: !20)
!97 = !DILocation(line: 255, column: 34, scope: !38)
!98 = !DILocation(line: 257, column: 21, scope: !38)
!99 = !DILocation(line: 257, column: 15, scope: !38)
!100 = !DILocation(line: 257, column: 2, scope: !38)
!101 = !DILocation(line: 257, column: 19, scope: !38)
!102 = !DILocation(line: 258, column: 2, scope: !38)
