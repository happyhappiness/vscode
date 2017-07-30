; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }

@lzma_header_magic = external constant [6 x i8], align 1
@lzma_footer_magic = external constant [2 x i8], align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_header_decode(%struct.lzma_stream_flags* %options, i8* %in) #0 !dbg !35 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %in.addr = alloca i8*, align 8
  %crc = alloca i32, align 4
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !85, metadata !86), !dbg !87
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !88, metadata !86), !dbg !89
  call void @llvm.dbg.declare(metadata i32* %crc, metadata !90, metadata !86), !dbg !91
  %0 = load i8*, i8** %in.addr, align 8, !dbg !92
  %call = call i32 @memcmp(i8* %0, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @lzma_header_magic, i32 0, i32 0), i64 6) #4, !dbg !94
  %cmp = icmp ne i32 %call, 0, !dbg !95
  br i1 %cmp, label %if.then, label %if.end, !dbg !96

if.then:                                          ; preds = %entry
  store i32 7, i32* %retval, align 4, !dbg !97
  br label %return, !dbg !97

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %in.addr, align 8, !dbg !98
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 6, !dbg !99
  %call1 = call i32 @lzma_crc32(i8* %add.ptr, i64 2, i32 0) #4, !dbg !100
  store i32 %call1, i32* %crc, align 4, !dbg !101
  %2 = load i32, i32* %crc, align 4, !dbg !102
  %3 = load i8*, i8** %in.addr, align 8, !dbg !104
  %add.ptr2 = getelementptr inbounds i8, i8* %3, i64 6, !dbg !105
  %add.ptr3 = getelementptr inbounds i8, i8* %add.ptr2, i64 2, !dbg !106
  %call4 = call i32 @read32le(i8* %add.ptr3), !dbg !107
  %cmp5 = icmp ne i32 %2, %call4, !dbg !108
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !109

if.then6:                                         ; preds = %if.end
  store i32 9, i32* %retval, align 4, !dbg !110
  br label %return, !dbg !110

if.end7:                                          ; preds = %if.end
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !111
  %5 = load i8*, i8** %in.addr, align 8, !dbg !113
  %add.ptr8 = getelementptr inbounds i8, i8* %5, i64 6, !dbg !114
  %call9 = call zeroext i1 @stream_flags_decode(%struct.lzma_stream_flags* %4, i8* %add.ptr8), !dbg !115
  br i1 %call9, label %if.then10, label %if.end11, !dbg !116

if.then10:                                        ; preds = %if.end7
  store i32 8, i32* %retval, align 4, !dbg !117
  br label %return, !dbg !117

if.end11:                                         ; preds = %if.end7
  %6 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !118
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %6, i32 0, i32 1, !dbg !119
  store i64 -1, i64* %backward_size, align 8, !dbg !120
  store i32 0, i32* %retval, align 4, !dbg !121
  br label %return, !dbg !121

return:                                           ; preds = %if.end11, %if.then10, %if.then6, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !122
  ret i32 %7, !dbg !122
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #2

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #2

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @read32le(i8* %buf) #3 !dbg !74 {
entry:
  %buf.addr = alloca i8*, align 8
  %num = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !123, metadata !86), !dbg !124
  call void @llvm.dbg.declare(metadata i32* %num, metadata !125, metadata !86), !dbg !126
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !127
  %1 = bitcast i8* %0 to i32*, !dbg !128
  %2 = load i32, i32* %1, align 4, !dbg !128
  store i32 %2, i32* %num, align 4, !dbg !126
  %3 = load i32, i32* %num, align 4, !dbg !129
  ret i32 %3, !dbg !130
}

; Function Attrs: nounwind uwtable
define internal zeroext i1 @stream_flags_decode(%struct.lzma_stream_flags* %options, i8* %in) #0 !dbg !78 {
entry:
  %retval = alloca i1, align 1
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %in.addr = alloca i8*, align 8
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !131, metadata !86), !dbg !132
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !133, metadata !86), !dbg !134
  %0 = load i8*, i8** %in.addr, align 8, !dbg !135
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !135
  %1 = load i8, i8* %arrayidx, align 1, !dbg !135
  %conv = zext i8 %1 to i32, !dbg !135
  %cmp = icmp ne i32 %conv, 0, !dbg !137
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !138

lor.lhs.false:                                    ; preds = %entry
  %2 = load i8*, i8** %in.addr, align 8, !dbg !139
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !139
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !139
  %conv3 = zext i8 %3 to i32, !dbg !139
  %and = and i32 %conv3, 240, !dbg !141
  %tobool = icmp ne i32 %and, 0, !dbg !141
  br i1 %tobool, label %if.then, label %if.end, !dbg !142

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i1 true, i1* %retval, align 1, !dbg !143
  br label %return, !dbg !143

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !144
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %4, i32 0, i32 0, !dbg !145
  store i32 0, i32* %version, align 8, !dbg !146
  %5 = load i8*, i8** %in.addr, align 8, !dbg !147
  %arrayidx4 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !147
  %6 = load i8, i8* %arrayidx4, align 1, !dbg !147
  %conv5 = zext i8 %6 to i32, !dbg !147
  %and6 = and i32 %conv5, 15, !dbg !148
  %7 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !149
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %7, i32 0, i32 2, !dbg !150
  store i32 %and6, i32* %check, align 8, !dbg !151
  store i1 false, i1* %retval, align 1, !dbg !152
  br label %return, !dbg !152

return:                                           ; preds = %if.end, %if.then
  %8 = load i1, i1* %retval, align 1, !dbg !153
  ret i1 %8, !dbg !153
}

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_footer_decode(%struct.lzma_stream_flags* %options, i8* %in) #0 !dbg !73 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %in.addr = alloca i8*, align 8
  %crc = alloca i32, align 4
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !154, metadata !86), !dbg !155
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !156, metadata !86), !dbg !157
  call void @llvm.dbg.declare(metadata i32* %crc, metadata !158, metadata !86), !dbg !159
  %0 = load i8*, i8** %in.addr, align 8, !dbg !160
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 8, !dbg !162
  %add.ptr1 = getelementptr inbounds i8, i8* %add.ptr, i64 2, !dbg !163
  %call = call i32 @memcmp(i8* %add.ptr1, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @lzma_footer_magic, i32 0, i32 0), i64 2) #4, !dbg !164
  %cmp = icmp ne i32 %call, 0, !dbg !165
  br i1 %cmp, label %if.then, label %if.end, !dbg !166

if.then:                                          ; preds = %entry
  store i32 7, i32* %retval, align 4, !dbg !167
  br label %return, !dbg !167

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %in.addr, align 8, !dbg !168
  %add.ptr2 = getelementptr inbounds i8, i8* %1, i64 4, !dbg !169
  %call3 = call i32 @lzma_crc32(i8* %add.ptr2, i64 6, i32 0) #4, !dbg !170
  store i32 %call3, i32* %crc, align 4, !dbg !171
  %2 = load i32, i32* %crc, align 4, !dbg !172
  %3 = load i8*, i8** %in.addr, align 8, !dbg !174
  %call4 = call i32 @read32le(i8* %3), !dbg !175
  %cmp5 = icmp ne i32 %2, %call4, !dbg !176
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !177

if.then6:                                         ; preds = %if.end
  store i32 9, i32* %retval, align 4, !dbg !178
  br label %return, !dbg !178

if.end7:                                          ; preds = %if.end
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !179
  %5 = load i8*, i8** %in.addr, align 8, !dbg !181
  %add.ptr8 = getelementptr inbounds i8, i8* %5, i64 8, !dbg !182
  %call9 = call zeroext i1 @stream_flags_decode(%struct.lzma_stream_flags* %4, i8* %add.ptr8), !dbg !183
  br i1 %call9, label %if.then10, label %if.end11, !dbg !184

if.then10:                                        ; preds = %if.end7
  store i32 8, i32* %retval, align 4, !dbg !185
  br label %return, !dbg !185

if.end11:                                         ; preds = %if.end7
  %6 = load i8*, i8** %in.addr, align 8, !dbg !186
  %add.ptr12 = getelementptr inbounds i8, i8* %6, i64 4, !dbg !187
  %call13 = call i32 @read32le(i8* %add.ptr12), !dbg !188
  %conv = zext i32 %call13 to i64, !dbg !188
  %7 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !189
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %7, i32 0, i32 1, !dbg !190
  store i64 %conv, i64* %backward_size, align 8, !dbg !191
  %8 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !192
  %backward_size14 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %8, i32 0, i32 1, !dbg !193
  %9 = load i64, i64* %backward_size14, align 8, !dbg !193
  %add = add i64 %9, 1, !dbg !194
  %mul = mul i64 %add, 4, !dbg !195
  %10 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !196
  %backward_size15 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %10, i32 0, i32 1, !dbg !197
  store i64 %mul, i64* %backward_size15, align 8, !dbg !198
  store i32 0, i32* %retval, align 4, !dbg !199
  br label %return, !dbg !199

return:                                           ; preds = %if.end11, %if.then10, %if.then6, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !200
  ret i32 %11, !dbg !200
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!82, !83}
!llvm.ident = !{!84}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !34)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!28 = !{!29, !31}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !32, line: 51, baseType: !33)
!32 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!34 = !{!35, !73, !74, !78}
!35 = distinct !DISubprogram(name: "lzma_stream_header_decode", scope: !1, file: !1, line: 31, type: !36, isLocal: false, isDefinition: true, scopeLine: 32, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !39, !69}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !41, line: 105, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 33, size: 448, align: 64, elements: !43)
!43 = !{!44, !45, !50, !52, !54, !55, !56, !57, !60, !61, !62, !63, !64, !65, !66, !67, !68}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !42, file: !41, line: 51, baseType: !31, size: 32, align: 32)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !42, file: !41, line: 69, baseType: !46, size: 64, align: 64, offset: 64)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !47, line: 63, baseType: !48)
!47 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !32, line: 55, baseType: !49)
!49 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !42, file: !41, line: 79, baseType: !51, size: 32, align: 32, offset: 128)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !42, file: !41, line: 90, baseType: !53, size: 32, align: 32, offset: 160)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !42, file: !41, line: 91, baseType: !53, size: 32, align: 32, offset: 192)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !42, file: !41, line: 92, baseType: !53, size: 32, align: 32, offset: 224)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !42, file: !41, line: 93, baseType: !53, size: 32, align: 32, offset: 256)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !42, file: !41, line: 94, baseType: !58, size: 8, align: 8, offset: 288)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !59)
!59 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !42, file: !41, line: 95, baseType: !58, size: 8, align: 8, offset: 296)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !42, file: !41, line: 96, baseType: !58, size: 8, align: 8, offset: 304)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !42, file: !41, line: 97, baseType: !58, size: 8, align: 8, offset: 312)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !42, file: !41, line: 98, baseType: !58, size: 8, align: 8, offset: 320)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !42, file: !41, line: 99, baseType: !58, size: 8, align: 8, offset: 328)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !42, file: !41, line: 100, baseType: !58, size: 8, align: 8, offset: 336)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !42, file: !41, line: 101, baseType: !58, size: 8, align: 8, offset: 344)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !42, file: !41, line: 102, baseType: !31, size: 32, align: 32, offset: 352)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !42, file: !41, line: 103, baseType: !31, size: 32, align: 32, offset: 384)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !71)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !32, line: 48, baseType: !59)
!72 = !{}
!73 = distinct !DISubprogram(name: "lzma_stream_footer_decode", scope: !1, file: !1, line: 62, type: !36, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!74 = distinct !DISubprogram(name: "read32le", scope: !75, file: !75, line: 209, type: !76, isLocal: true, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!75 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!76 = !DISubroutineType(types: !77)
!77 = !{!31, !69}
!78 = distinct !DISubprogram(name: "stream_flags_decode", scope: !1, file: !1, line: 17, type: !79, isLocal: true, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!79 = !DISubroutineType(types: !80)
!80 = !{!81, !39, !69}
!81 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!82 = !{i32 2, !"Dwarf Version", i32 4}
!83 = !{i32 2, !"Debug Info Version", i32 3}
!84 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!85 = !DILocalVariable(name: "options", arg: 1, scope: !35, file: !1, line: 31, type: !39)
!86 = !DIExpression()
!87 = !DILocation(line: 31, column: 46, scope: !35)
!88 = !DILocalVariable(name: "in", arg: 2, scope: !35, file: !1, line: 31, type: !69)
!89 = !DILocation(line: 31, column: 70, scope: !35)
!90 = !DILocalVariable(name: "crc", scope: !35, file: !1, line: 33, type: !31)
!91 = !DILocation(line: 33, column: 11, scope: !35)
!92 = !DILocation(line: 36, column: 13, scope: !93)
!93 = distinct !DILexicalBlock(scope: !35, file: !1, line: 36, column: 6)
!94 = !DILocation(line: 36, column: 6, scope: !93)
!95 = !DILocation(line: 36, column: 63, scope: !93)
!96 = !DILocation(line: 36, column: 6, scope: !35)
!97 = !DILocation(line: 37, column: 3, scope: !93)
!98 = !DILocation(line: 41, column: 19, scope: !35)
!99 = !DILocation(line: 41, column: 22, scope: !35)
!100 = !DILocation(line: 41, column: 8, scope: !35)
!101 = !DILocation(line: 41, column: 6, scope: !35)
!102 = !DILocation(line: 43, column: 6, scope: !103)
!103 = distinct !DILexicalBlock(scope: !35, file: !1, line: 43, column: 6)
!104 = !DILocation(line: 43, column: 32, scope: !103)
!105 = !DILocation(line: 43, column: 35, scope: !103)
!106 = !DILocation(line: 44, column: 4, scope: !103)
!107 = !DILocation(line: 43, column: 13, scope: !103)
!108 = !DILocation(line: 43, column: 10, scope: !103)
!109 = !DILocation(line: 43, column: 6, scope: !35)
!110 = !DILocation(line: 45, column: 3, scope: !103)
!111 = !DILocation(line: 48, column: 26, scope: !112)
!112 = distinct !DILexicalBlock(scope: !35, file: !1, line: 48, column: 6)
!113 = !DILocation(line: 48, column: 35, scope: !112)
!114 = !DILocation(line: 48, column: 38, scope: !112)
!115 = !DILocation(line: 48, column: 6, scope: !112)
!116 = !DILocation(line: 48, column: 6, scope: !35)
!117 = !DILocation(line: 49, column: 3, scope: !112)
!118 = !DILocation(line: 55, column: 2, scope: !35)
!119 = !DILocation(line: 55, column: 11, scope: !35)
!120 = !DILocation(line: 55, column: 25, scope: !35)
!121 = !DILocation(line: 57, column: 2, scope: !35)
!122 = !DILocation(line: 58, column: 1, scope: !35)
!123 = !DILocalVariable(name: "buf", arg: 1, scope: !74, file: !75, line: 209, type: !69)
!124 = !DILocation(line: 209, column: 25, scope: !74)
!125 = !DILocalVariable(name: "num", scope: !74, file: !75, line: 211, type: !31)
!126 = !DILocation(line: 211, column: 11, scope: !74)
!127 = !DILocation(line: 211, column: 36, scope: !74)
!128 = !DILocation(line: 211, column: 17, scope: !74)
!129 = !DILocation(line: 212, column: 9, scope: !74)
!130 = !DILocation(line: 212, column: 2, scope: !74)
!131 = !DILocalVariable(name: "options", arg: 1, scope: !78, file: !1, line: 17, type: !39)
!132 = !DILocation(line: 17, column: 40, scope: !78)
!133 = !DILocalVariable(name: "in", arg: 2, scope: !78, file: !1, line: 17, type: !69)
!134 = !DILocation(line: 17, column: 64, scope: !78)
!135 = !DILocation(line: 20, column: 6, scope: !136)
!136 = distinct !DILexicalBlock(scope: !78, file: !1, line: 20, column: 6)
!137 = !DILocation(line: 20, column: 12, scope: !136)
!138 = !DILocation(line: 20, column: 20, scope: !136)
!139 = !DILocation(line: 20, column: 24, scope: !140)
!140 = !DILexicalBlockFile(scope: !136, file: !1, discriminator: 1)
!141 = !DILocation(line: 20, column: 30, scope: !140)
!142 = !DILocation(line: 20, column: 6, scope: !140)
!143 = !DILocation(line: 21, column: 3, scope: !136)
!144 = !DILocation(line: 23, column: 2, scope: !78)
!145 = !DILocation(line: 23, column: 11, scope: !78)
!146 = !DILocation(line: 23, column: 19, scope: !78)
!147 = !DILocation(line: 24, column: 19, scope: !78)
!148 = !DILocation(line: 24, column: 25, scope: !78)
!149 = !DILocation(line: 24, column: 2, scope: !78)
!150 = !DILocation(line: 24, column: 11, scope: !78)
!151 = !DILocation(line: 24, column: 17, scope: !78)
!152 = !DILocation(line: 26, column: 2, scope: !78)
!153 = !DILocation(line: 27, column: 1, scope: !78)
!154 = !DILocalVariable(name: "options", arg: 1, scope: !73, file: !1, line: 62, type: !39)
!155 = !DILocation(line: 62, column: 46, scope: !73)
!156 = !DILocalVariable(name: "in", arg: 2, scope: !73, file: !1, line: 62, type: !69)
!157 = !DILocation(line: 62, column: 70, scope: !73)
!158 = !DILocalVariable(name: "crc", scope: !73, file: !1, line: 64, type: !31)
!159 = !DILocation(line: 64, column: 11, scope: !73)
!160 = !DILocation(line: 67, column: 13, scope: !161)
!161 = distinct !DILexicalBlock(scope: !73, file: !1, line: 67, column: 6)
!162 = !DILocation(line: 67, column: 16, scope: !161)
!163 = !DILocation(line: 67, column: 39, scope: !161)
!164 = !DILocation(line: 67, column: 6, scope: !161)
!165 = !DILocation(line: 68, column: 50, scope: !161)
!166 = !DILocation(line: 67, column: 6, scope: !73)
!167 = !DILocation(line: 69, column: 3, scope: !161)
!168 = !DILocation(line: 72, column: 19, scope: !73)
!169 = !DILocation(line: 72, column: 22, scope: !73)
!170 = !DILocation(line: 72, column: 8, scope: !73)
!171 = !DILocation(line: 72, column: 6, scope: !73)
!172 = !DILocation(line: 74, column: 6, scope: !173)
!173 = distinct !DILexicalBlock(scope: !73, file: !1, line: 74, column: 6)
!174 = !DILocation(line: 74, column: 32, scope: !173)
!175 = !DILocation(line: 74, column: 13, scope: !173)
!176 = !DILocation(line: 74, column: 10, scope: !173)
!177 = !DILocation(line: 74, column: 6, scope: !73)
!178 = !DILocation(line: 75, column: 3, scope: !173)
!179 = !DILocation(line: 78, column: 26, scope: !180)
!180 = distinct !DILexicalBlock(scope: !73, file: !1, line: 78, column: 6)
!181 = !DILocation(line: 78, column: 35, scope: !180)
!182 = !DILocation(line: 78, column: 38, scope: !180)
!183 = !DILocation(line: 78, column: 6, scope: !180)
!184 = !DILocation(line: 78, column: 6, scope: !73)
!185 = !DILocation(line: 79, column: 3, scope: !180)
!186 = !DILocation(line: 82, column: 46, scope: !73)
!187 = !DILocation(line: 82, column: 49, scope: !73)
!188 = !DILocation(line: 82, column: 27, scope: !73)
!189 = !DILocation(line: 82, column: 2, scope: !73)
!190 = !DILocation(line: 82, column: 11, scope: !73)
!191 = !DILocation(line: 82, column: 25, scope: !73)
!192 = !DILocation(line: 83, column: 28, scope: !73)
!193 = !DILocation(line: 83, column: 37, scope: !73)
!194 = !DILocation(line: 83, column: 51, scope: !73)
!195 = !DILocation(line: 83, column: 56, scope: !73)
!196 = !DILocation(line: 83, column: 2, scope: !73)
!197 = !DILocation(line: 83, column: 11, scope: !73)
!198 = !DILocation(line: 83, column: 25, scope: !73)
!199 = !DILocation(line: 85, column: 2, scope: !73)
!200 = !DILocation(line: 86, column: 1, scope: !73)
