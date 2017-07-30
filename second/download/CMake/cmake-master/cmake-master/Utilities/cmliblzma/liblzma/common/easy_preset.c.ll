; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_options_easy = type { [5 x %struct.lzma_filter], %struct.lzma_options_lzma }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

; Function Attrs: nounwind uwtable
define zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy* %opt_easy, i32 %preset) #0 !dbg !20 {
entry:
  %retval = alloca i1, align 1
  %opt_easy.addr = alloca %struct.lzma_options_easy*, align 8
  %preset.addr = alloca i32, align 4
  store %struct.lzma_options_easy* %opt_easy, %struct.lzma_options_easy** %opt_easy.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_easy** %opt_easy.addr, metadata !86, metadata !87), !dbg !88
  store i32 %preset, i32* %preset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %preset.addr, metadata !89, metadata !87), !dbg !90
  %0 = load %struct.lzma_options_easy*, %struct.lzma_options_easy** %opt_easy.addr, align 8, !dbg !91
  %opt_lzma = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %0, i32 0, i32 1, !dbg !93
  %1 = load i32, i32* %preset.addr, align 4, !dbg !94
  %call = call zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma* %opt_lzma, i32 %1) #3, !dbg !95
  %tobool = icmp ne i8 %call, 0, !dbg !95
  br i1 %tobool, label %if.then, label %if.end, !dbg !96

if.then:                                          ; preds = %entry
  store i1 true, i1* %retval, align 1, !dbg !97
  br label %return, !dbg !97

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_options_easy*, %struct.lzma_options_easy** %opt_easy.addr, align 8, !dbg !98
  %filters = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %2, i32 0, i32 0, !dbg !99
  %arrayidx = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !98
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !100
  store i64 33, i64* %id, align 8, !dbg !101
  %3 = load %struct.lzma_options_easy*, %struct.lzma_options_easy** %opt_easy.addr, align 8, !dbg !102
  %opt_lzma1 = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %3, i32 0, i32 1, !dbg !103
  %4 = bitcast %struct.lzma_options_lzma* %opt_lzma1 to i8*, !dbg !104
  %5 = load %struct.lzma_options_easy*, %struct.lzma_options_easy** %opt_easy.addr, align 8, !dbg !105
  %filters2 = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %5, i32 0, i32 0, !dbg !106
  %arrayidx3 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters2, i64 0, i64 0, !dbg !105
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx3, i32 0, i32 1, !dbg !107
  store i8* %4, i8** %options, align 8, !dbg !108
  %6 = load %struct.lzma_options_easy*, %struct.lzma_options_easy** %opt_easy.addr, align 8, !dbg !109
  %filters4 = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %6, i32 0, i32 0, !dbg !110
  %arrayidx5 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters4, i64 0, i64 1, !dbg !109
  %id6 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx5, i32 0, i32 0, !dbg !111
  store i64 -1, i64* %id6, align 8, !dbg !112
  store i1 false, i1* %retval, align 1, !dbg !113
  br label %return, !dbg !113

return:                                           ; preds = %if.end, %if.then
  %7 = load i1, i1* %retval, align 1, !dbg !114
  ret i1 %7, !dbg !114
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma*, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!83, !84}
!llvm.ident = !{!85}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !19)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !8, !15}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 138, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7}
!6 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!7 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!8 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 58, size: 32, align: 32, elements: !9)
!9 = !{!10, !11, !12, !13, !14}
!10 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!11 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!12 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!13 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!14 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 44, size: 32, align: 32, elements: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!17 = !{!18}
!18 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!19 = !{!20}
!20 = distinct !DISubprogram(name: "lzma_easy_preset", scope: !1, file: !1, line: 17, type: !21, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !82)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24, !50}
!23 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_easy", file: !26, line: 27, baseType: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!27 = !DICompositeType(tag: DW_TAG_structure_type, file: !26, line: 16, size: 1536, align: 64, elements: !28)
!28 = !{!29, !45}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !27, file: !26, line: 19, baseType: !30, size: 640, align: 64)
!30 = !DICompositeType(tag: DW_TAG_array_type, baseType: !31, size: 640, align: 64, elements: !43)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !32, line: 65, baseType: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DICompositeType(tag: DW_TAG_structure_type, file: !32, line: 43, size: 128, align: 64, elements: !34)
!34 = !{!35, !41}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !33, file: !32, line: 54, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !37, line: 63, baseType: !38)
!37 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !39, line: 55, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!40 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !33, file: !32, line: 63, baseType: !42, size: 64, align: 64, offset: 64)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!43 = !{!44}
!44 = !DISubrange(count: 5)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "opt_lzma", scope: !27, file: !26, line: 22, baseType: !46, size: 896, align: 64, offset: 640)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !4, line: 399, baseType: !47)
!47 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 185, size: 896, align: 64, elements: !48)
!48 = !{!49, !52, !57, !58, !59, !60, !61, !63, !64, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !77, !78, !79, !80, !81}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !47, file: !4, line: 217, baseType: !50, size: 32, align: 32)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !39, line: 51, baseType: !51)
!51 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !47, file: !4, line: 240, baseType: !53, size: 64, align: 64, offset: 64)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !39, line: 48, baseType: !56)
!56 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !47, file: !4, line: 254, baseType: !50, size: 32, align: 32, offset: 128)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !47, file: !4, line: 281, baseType: !50, size: 32, align: 32, offset: 160)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !47, file: !4, line: 293, baseType: !50, size: 32, align: 32, offset: 192)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !47, file: !4, line: 316, baseType: !50, size: 32, align: 32, offset: 224)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !47, file: !4, line: 322, baseType: !62, size: 32, align: 32, offset: 256)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !4, line: 155, baseType: !3)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !47, file: !4, line: 342, baseType: !50, size: 32, align: 32, offset: 288)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !47, file: !4, line: 345, baseType: !65, size: 32, align: 32, offset: 320)
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !4, line: 111, baseType: !8)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !47, file: !4, line: 375, baseType: !50, size: 32, align: 32, offset: 352)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !47, file: !4, line: 384, baseType: !50, size: 32, align: 32, offset: 384)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !47, file: !4, line: 385, baseType: !50, size: 32, align: 32, offset: 416)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !47, file: !4, line: 386, baseType: !50, size: 32, align: 32, offset: 448)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !47, file: !4, line: 387, baseType: !50, size: 32, align: 32, offset: 480)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !47, file: !4, line: 388, baseType: !50, size: 32, align: 32, offset: 512)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !47, file: !4, line: 389, baseType: !50, size: 32, align: 32, offset: 544)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !47, file: !4, line: 390, baseType: !50, size: 32, align: 32, offset: 576)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !47, file: !4, line: 391, baseType: !50, size: 32, align: 32, offset: 608)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !47, file: !4, line: 392, baseType: !76, size: 32, align: 32, offset: 640)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !16, line: 46, baseType: !15)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !47, file: !4, line: 393, baseType: !76, size: 32, align: 32, offset: 672)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !47, file: !4, line: 394, baseType: !76, size: 32, align: 32, offset: 704)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !47, file: !4, line: 395, baseType: !76, size: 32, align: 32, offset: 736)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !47, file: !4, line: 396, baseType: !42, size: 64, align: 64, offset: 768)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !47, file: !4, line: 397, baseType: !42, size: 64, align: 64, offset: 832)
!82 = !{}
!83 = !{i32 2, !"Dwarf Version", i32 4}
!84 = !{i32 2, !"Debug Info Version", i32 3}
!85 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!86 = !DILocalVariable(name: "opt_easy", arg: 1, scope: !20, file: !1, line: 17, type: !24)
!87 = !DIExpression()
!88 = !DILocation(line: 17, column: 37, scope: !20)
!89 = !DILocalVariable(name: "preset", arg: 2, scope: !20, file: !1, line: 17, type: !50)
!90 = !DILocation(line: 17, column: 56, scope: !20)
!91 = !DILocation(line: 19, column: 24, scope: !92)
!92 = distinct !DILexicalBlock(scope: !20, file: !1, line: 19, column: 6)
!93 = !DILocation(line: 19, column: 34, scope: !92)
!94 = !DILocation(line: 19, column: 44, scope: !92)
!95 = !DILocation(line: 19, column: 6, scope: !92)
!96 = !DILocation(line: 19, column: 6, scope: !20)
!97 = !DILocation(line: 20, column: 3, scope: !92)
!98 = !DILocation(line: 22, column: 2, scope: !20)
!99 = !DILocation(line: 22, column: 12, scope: !20)
!100 = !DILocation(line: 22, column: 23, scope: !20)
!101 = !DILocation(line: 22, column: 26, scope: !20)
!102 = !DILocation(line: 23, column: 34, scope: !20)
!103 = !DILocation(line: 23, column: 44, scope: !20)
!104 = !DILocation(line: 23, column: 33, scope: !20)
!105 = !DILocation(line: 23, column: 2, scope: !20)
!106 = !DILocation(line: 23, column: 12, scope: !20)
!107 = !DILocation(line: 23, column: 23, scope: !20)
!108 = !DILocation(line: 23, column: 31, scope: !20)
!109 = !DILocation(line: 24, column: 2, scope: !20)
!110 = !DILocation(line: 24, column: 12, scope: !20)
!111 = !DILocation(line: 24, column: 23, scope: !20)
!112 = !DILocation(line: 24, column: 26, scope: !20)
!113 = !DILocation(line: 26, column: 2, scope: !20)
!114 = !DILocation(line: 27, column: 1, scope: !20)
