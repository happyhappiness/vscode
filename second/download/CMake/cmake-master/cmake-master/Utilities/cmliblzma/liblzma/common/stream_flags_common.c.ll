; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_common.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }

@lzma_header_magic = constant [6 x i8] c"\FD7zXZ\00", align 1
@lzma_footer_magic = constant [2 x i8] c"YZ", align 1

; Function Attrs: nounwind readonly uwtable
define i32 @lzma_stream_flags_compare(%struct.lzma_stream_flags* %a, %struct.lzma_stream_flags* %b) #0 !dbg !31 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.lzma_stream_flags*, align 8
  %b.addr = alloca %struct.lzma_stream_flags*, align 8
  store %struct.lzma_stream_flags* %a, %struct.lzma_stream_flags** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %a.addr, metadata !88, metadata !89), !dbg !90
  store %struct.lzma_stream_flags* %b, %struct.lzma_stream_flags** %b.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %b.addr, metadata !91, metadata !89), !dbg !92
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !93
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 0, !dbg !95
  %1 = load i32, i32* %version, align 8, !dbg !95
  %cmp = icmp ne i32 %1, 0, !dbg !96
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !97

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !98
  %version1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %2, i32 0, i32 0, !dbg !100
  %3 = load i32, i32* %version1, align 8, !dbg !100
  %cmp2 = icmp ne i32 %3, 0, !dbg !101
  br i1 %cmp2, label %if.then, label %if.end, !dbg !102

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 8, i32* %retval, align 4, !dbg !103
  br label %return, !dbg !103

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !104
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %4, i32 0, i32 2, !dbg !106
  %5 = load i32, i32* %check, align 8, !dbg !106
  %cmp3 = icmp ugt i32 %5, 15, !dbg !107
  br i1 %cmp3, label %if.then7, label %lor.lhs.false4, !dbg !108

lor.lhs.false4:                                   ; preds = %if.end
  %6 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !109
  %check5 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %6, i32 0, i32 2, !dbg !111
  %7 = load i32, i32* %check5, align 8, !dbg !111
  %cmp6 = icmp ugt i32 %7, 15, !dbg !112
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !113

if.then7:                                         ; preds = %lor.lhs.false4, %if.end
  store i32 11, i32* %retval, align 4, !dbg !115
  br label %return, !dbg !115

if.end8:                                          ; preds = %lor.lhs.false4
  %8 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !116
  %check9 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %8, i32 0, i32 2, !dbg !118
  %9 = load i32, i32* %check9, align 8, !dbg !118
  %10 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !119
  %check10 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %10, i32 0, i32 2, !dbg !120
  %11 = load i32, i32* %check10, align 8, !dbg !120
  %cmp11 = icmp ne i32 %9, %11, !dbg !121
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !122

if.then12:                                        ; preds = %if.end8
  store i32 9, i32* %retval, align 4, !dbg !123
  br label %return, !dbg !123

if.end13:                                         ; preds = %if.end8
  %12 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !124
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %12, i32 0, i32 1, !dbg !126
  %13 = load i64, i64* %backward_size, align 8, !dbg !126
  %cmp14 = icmp ne i64 %13, -1, !dbg !127
  br i1 %cmp14, label %land.lhs.true, label %if.end27, !dbg !128

land.lhs.true:                                    ; preds = %if.end13
  %14 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !129
  %backward_size15 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %14, i32 0, i32 1, !dbg !131
  %15 = load i64, i64* %backward_size15, align 8, !dbg !131
  %cmp16 = icmp ne i64 %15, -1, !dbg !132
  br i1 %cmp16, label %if.then17, label %if.end27, !dbg !133

if.then17:                                        ; preds = %land.lhs.true
  %16 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !134
  %call = call zeroext i1 @is_backward_size_valid(%struct.lzma_stream_flags* %16), !dbg !137
  br i1 %call, label %lor.lhs.false18, label %if.then20, !dbg !138

lor.lhs.false18:                                  ; preds = %if.then17
  %17 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !139
  %call19 = call zeroext i1 @is_backward_size_valid(%struct.lzma_stream_flags* %17), !dbg !141
  br i1 %call19, label %if.end21, label %if.then20, !dbg !142

if.then20:                                        ; preds = %lor.lhs.false18, %if.then17
  store i32 11, i32* %retval, align 4, !dbg !143
  br label %return, !dbg !143

if.end21:                                         ; preds = %lor.lhs.false18
  %18 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %a.addr, align 8, !dbg !144
  %backward_size22 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %18, i32 0, i32 1, !dbg !146
  %19 = load i64, i64* %backward_size22, align 8, !dbg !146
  %20 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %b.addr, align 8, !dbg !147
  %backward_size23 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %20, i32 0, i32 1, !dbg !148
  %21 = load i64, i64* %backward_size23, align 8, !dbg !148
  %cmp24 = icmp ne i64 %19, %21, !dbg !149
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !150

if.then25:                                        ; preds = %if.end21
  store i32 9, i32* %retval, align 4, !dbg !151
  br label %return, !dbg !151

if.end26:                                         ; preds = %if.end21
  br label %if.end27, !dbg !152

if.end27:                                         ; preds = %if.end26, %land.lhs.true, %if.end13
  store i32 0, i32* %retval, align 4, !dbg !153
  br label %return, !dbg !153

return:                                           ; preds = %if.end27, %if.then25, %if.then20, %if.then12, %if.then7, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !154
  ret i32 %22, !dbg !154
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @is_backward_size_valid(%struct.lzma_stream_flags* %options) #2 !dbg !69 {
entry:
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !155, metadata !89), !dbg !156
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !157
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 1, !dbg !158
  %1 = load i64, i64* %backward_size, align 8, !dbg !158
  %cmp = icmp uge i64 %1, 4, !dbg !159
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !160

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !161
  %backward_size1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %2, i32 0, i32 1, !dbg !163
  %3 = load i64, i64* %backward_size1, align 8, !dbg !163
  %cmp2 = icmp ule i64 %3, 17179869184, !dbg !164
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !165

land.rhs:                                         ; preds = %land.lhs.true
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !166
  %backward_size3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %4, i32 0, i32 1, !dbg !167
  %5 = load i64, i64* %backward_size3, align 8, !dbg !167
  %and = and i64 %5, 3, !dbg !168
  %cmp4 = icmp eq i64 %and, 0, !dbg !169
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %entry
  %6 = phi i1 [ false, %land.lhs.true ], [ false, %entry ], [ %cmp4, %land.rhs ]
  ret i1 %6, !dbg !170
}

attributes #0 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!85, !86}
!llvm.ident = !{!87}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !30, globals: !74)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_common.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !26)
!26 = !{!27}
!27 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!28 = !{!29}
!29 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!30 = !{!31, !69}
!31 = distinct !DISubprogram(name: "lzma_stream_flags_compare", scope: !1, file: !1, line: 21, type: !32, isLocal: false, isDefinition: true, scopeLine: 23, flags: DIFlagPrototyped, isOptimized: false, variables: !68)
!32 = !DISubroutineType(types: !33)
!33 = !{!34, !35, !35}
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !38, line: 105, baseType: !39)
!38 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!39 = !DICompositeType(tag: DW_TAG_structure_type, file: !38, line: 33, size: 448, align: 64, elements: !40)
!40 = !{!41, !44, !49, !51, !53, !54, !55, !56, !59, !60, !61, !62, !63, !64, !65, !66, !67}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !39, file: !38, line: 51, baseType: !42, size: 32, align: 32)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !43, line: 51, baseType: !29)
!43 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!44 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !39, file: !38, line: 69, baseType: !45, size: 64, align: 64, offset: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !46, line: 63, baseType: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !43, line: 55, baseType: !48)
!48 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !39, file: !38, line: 79, baseType: !50, size: 32, align: 32, offset: 128)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !39, file: !38, line: 90, baseType: !52, size: 32, align: 32, offset: 160)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !39, file: !38, line: 91, baseType: !52, size: 32, align: 32, offset: 192)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !39, file: !38, line: 92, baseType: !52, size: 32, align: 32, offset: 224)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !39, file: !38, line: 93, baseType: !52, size: 32, align: 32, offset: 256)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !39, file: !38, line: 94, baseType: !57, size: 8, align: 8, offset: 288)
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !58)
!58 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !39, file: !38, line: 95, baseType: !57, size: 8, align: 8, offset: 296)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !39, file: !38, line: 96, baseType: !57, size: 8, align: 8, offset: 304)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !39, file: !38, line: 97, baseType: !57, size: 8, align: 8, offset: 312)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !39, file: !38, line: 98, baseType: !57, size: 8, align: 8, offset: 320)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !39, file: !38, line: 99, baseType: !57, size: 8, align: 8, offset: 328)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !39, file: !38, line: 100, baseType: !57, size: 8, align: 8, offset: 336)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !39, file: !38, line: 101, baseType: !57, size: 8, align: 8, offset: 344)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !39, file: !38, line: 102, baseType: !42, size: 32, align: 32, offset: 352)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !39, file: !38, line: 103, baseType: !42, size: 32, align: 32, offset: 384)
!68 = !{}
!69 = distinct !DISubprogram(name: "is_backward_size_valid", scope: !70, file: !70, line: 26, type: !71, isLocal: true, isDefinition: true, scopeLine: 27, flags: DIFlagPrototyped, isOptimized: false, variables: !68)
!70 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!71 = !DISubroutineType(types: !72)
!72 = !{!73, !35}
!73 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!74 = !{!75, !81}
!75 = !DIGlobalVariable(name: "lzma_header_magic", scope: !0, file: !1, line: 16, type: !76, isLocal: false, isDefinition: true, variable: [6 x i8]* @lzma_header_magic)
!76 = !DICompositeType(tag: DW_TAG_array_type, baseType: !77, size: 48, align: 8, elements: !79)
!77 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !78)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !43, line: 48, baseType: !58)
!79 = !{!80}
!80 = !DISubrange(count: 6)
!81 = !DIGlobalVariable(name: "lzma_footer_magic", scope: !0, file: !1, line: 17, type: !82, isLocal: false, isDefinition: true, variable: [2 x i8]* @lzma_footer_magic)
!82 = !DICompositeType(tag: DW_TAG_array_type, baseType: !77, size: 16, align: 8, elements: !83)
!83 = !{!84}
!84 = !DISubrange(count: 2)
!85 = !{i32 2, !"Dwarf Version", i32 4}
!86 = !{i32 2, !"Debug Info Version", i32 3}
!87 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!88 = !DILocalVariable(name: "a", arg: 1, scope: !31, file: !1, line: 22, type: !35)
!89 = !DIExpression()
!90 = !DILocation(line: 22, column: 28, scope: !31)
!91 = !DILocalVariable(name: "b", arg: 2, scope: !31, file: !1, line: 22, type: !35)
!92 = !DILocation(line: 22, column: 56, scope: !31)
!93 = !DILocation(line: 25, column: 6, scope: !94)
!94 = distinct !DILexicalBlock(scope: !31, file: !1, line: 25, column: 6)
!95 = !DILocation(line: 25, column: 9, scope: !94)
!96 = !DILocation(line: 25, column: 17, scope: !94)
!97 = !DILocation(line: 25, column: 22, scope: !94)
!98 = !DILocation(line: 25, column: 25, scope: !99)
!99 = !DILexicalBlockFile(scope: !94, file: !1, discriminator: 1)
!100 = !DILocation(line: 25, column: 28, scope: !99)
!101 = !DILocation(line: 25, column: 36, scope: !99)
!102 = !DILocation(line: 25, column: 6, scope: !99)
!103 = !DILocation(line: 26, column: 3, scope: !94)
!104 = !DILocation(line: 29, column: 21, scope: !105)
!105 = distinct !DILexicalBlock(scope: !31, file: !1, line: 29, column: 6)
!106 = !DILocation(line: 29, column: 24, scope: !105)
!107 = !DILocation(line: 29, column: 31, scope: !105)
!108 = !DILocation(line: 30, column: 4, scope: !105)
!109 = !DILocation(line: 30, column: 22, scope: !110)
!110 = !DILexicalBlockFile(scope: !105, file: !1, discriminator: 1)
!111 = !DILocation(line: 30, column: 25, scope: !110)
!112 = !DILocation(line: 30, column: 32, scope: !110)
!113 = !DILocation(line: 29, column: 6, scope: !114)
!114 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 1)
!115 = !DILocation(line: 31, column: 3, scope: !105)
!116 = !DILocation(line: 33, column: 6, scope: !117)
!117 = distinct !DILexicalBlock(scope: !31, file: !1, line: 33, column: 6)
!118 = !DILocation(line: 33, column: 9, scope: !117)
!119 = !DILocation(line: 33, column: 18, scope: !117)
!120 = !DILocation(line: 33, column: 21, scope: !117)
!121 = !DILocation(line: 33, column: 15, scope: !117)
!122 = !DILocation(line: 33, column: 6, scope: !31)
!123 = !DILocation(line: 34, column: 3, scope: !117)
!124 = !DILocation(line: 37, column: 6, scope: !125)
!125 = distinct !DILexicalBlock(scope: !31, file: !1, line: 37, column: 6)
!126 = !DILocation(line: 37, column: 9, scope: !125)
!127 = !DILocation(line: 37, column: 23, scope: !125)
!128 = !DILocation(line: 38, column: 4, scope: !125)
!129 = !DILocation(line: 38, column: 7, scope: !130)
!130 = !DILexicalBlockFile(scope: !125, file: !1, discriminator: 1)
!131 = !DILocation(line: 38, column: 10, scope: !130)
!132 = !DILocation(line: 38, column: 24, scope: !130)
!133 = !DILocation(line: 37, column: 6, scope: !114)
!134 = !DILocation(line: 39, column: 31, scope: !135)
!135 = distinct !DILexicalBlock(scope: !136, file: !1, line: 39, column: 7)
!136 = distinct !DILexicalBlock(scope: !125, file: !1, line: 38, column: 45)
!137 = !DILocation(line: 39, column: 8, scope: !135)
!138 = !DILocation(line: 39, column: 34, scope: !135)
!139 = !DILocation(line: 39, column: 61, scope: !140)
!140 = !DILexicalBlockFile(scope: !135, file: !1, discriminator: 1)
!141 = !DILocation(line: 39, column: 38, scope: !140)
!142 = !DILocation(line: 39, column: 7, scope: !140)
!143 = !DILocation(line: 40, column: 4, scope: !135)
!144 = !DILocation(line: 42, column: 7, scope: !145)
!145 = distinct !DILexicalBlock(scope: !136, file: !1, line: 42, column: 7)
!146 = !DILocation(line: 42, column: 10, scope: !145)
!147 = !DILocation(line: 42, column: 27, scope: !145)
!148 = !DILocation(line: 42, column: 30, scope: !145)
!149 = !DILocation(line: 42, column: 24, scope: !145)
!150 = !DILocation(line: 42, column: 7, scope: !136)
!151 = !DILocation(line: 43, column: 4, scope: !145)
!152 = !DILocation(line: 44, column: 2, scope: !136)
!153 = !DILocation(line: 46, column: 2, scope: !31)
!154 = !DILocation(line: 47, column: 1, scope: !31)
!155 = !DILocalVariable(name: "options", arg: 1, scope: !69, file: !70, line: 26, type: !35)
!156 = !DILocation(line: 26, column: 49, scope: !69)
!157 = !DILocation(line: 28, column: 9, scope: !69)
!158 = !DILocation(line: 28, column: 18, scope: !69)
!159 = !DILocation(line: 28, column: 32, scope: !69)
!160 = !DILocation(line: 29, column: 4, scope: !69)
!161 = !DILocation(line: 29, column: 7, scope: !162)
!162 = !DILexicalBlockFile(scope: !69, file: !70, discriminator: 1)
!163 = !DILocation(line: 29, column: 16, scope: !162)
!164 = !DILocation(line: 29, column: 30, scope: !162)
!165 = !DILocation(line: 30, column: 4, scope: !69)
!166 = !DILocation(line: 30, column: 8, scope: !162)
!167 = !DILocation(line: 30, column: 17, scope: !162)
!168 = !DILocation(line: 30, column: 31, scope: !162)
!169 = !DILocation(line: 30, column: 36, scope: !162)
!170 = !DILocation(line: 28, column: 2, scope: !162)
