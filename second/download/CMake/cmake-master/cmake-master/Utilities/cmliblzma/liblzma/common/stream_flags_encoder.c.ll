; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }

@lzma_header_magic = external constant [6 x i8], align 1
@lzma_footer_magic = external constant [2 x i8], align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_header_encode(%struct.lzma_stream_flags* %options, i8* %out) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %out.addr = alloca i8*, align 8
  %crc = alloca i32, align 4
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !88, metadata !89), !dbg !90
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !91, metadata !89), !dbg !92
  call void @llvm.dbg.declare(metadata i32* %crc, metadata !93, metadata !89), !dbg !94
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !95
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 0, !dbg !97
  %1 = load i32, i32* %version, align 8, !dbg !97
  %cmp = icmp ne i32 %1, 0, !dbg !98
  br i1 %cmp, label %if.then, label %if.end, !dbg !99

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !100
  br label %return, !dbg !100

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %out.addr, align 8, !dbg !101
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @lzma_header_magic, i32 0, i32 0), i64 6, i32 1, i1 false), !dbg !102
  %3 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !103
  %4 = load i8*, i8** %out.addr, align 8, !dbg !105
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 6, !dbg !106
  %call = call zeroext i1 @stream_flags_encode(%struct.lzma_stream_flags* %3, i8* %add.ptr), !dbg !107
  br i1 %call, label %if.then1, label %if.end2, !dbg !108

if.then1:                                         ; preds = %if.end
  store i32 11, i32* %retval, align 4, !dbg !109
  br label %return, !dbg !109

if.end2:                                          ; preds = %if.end
  %5 = load i8*, i8** %out.addr, align 8, !dbg !110
  %add.ptr3 = getelementptr inbounds i8, i8* %5, i64 6, !dbg !111
  %call4 = call i32 @lzma_crc32(i8* %add.ptr3, i64 2, i32 0) #5, !dbg !112
  store i32 %call4, i32* %crc, align 4, !dbg !113
  %6 = load i8*, i8** %out.addr, align 8, !dbg !114
  %add.ptr5 = getelementptr inbounds i8, i8* %6, i64 6, !dbg !114
  %add.ptr6 = getelementptr inbounds i8, i8* %add.ptr5, i64 2, !dbg !114
  %7 = load i32, i32* %crc, align 4, !dbg !114
  call void @write32ne(i8* %add.ptr6, i32 %7), !dbg !114
  store i32 0, i32* %retval, align 4, !dbg !115
  br label %return, !dbg !115

return:                                           ; preds = %if.end2, %if.then1, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !116
  ret i32 %8, !dbg !116
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal zeroext i1 @stream_flags_encode(%struct.lzma_stream_flags* %options, i8* %out) #0 !dbg !73 {
entry:
  %retval = alloca i1, align 1
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %out.addr = alloca i8*, align 8
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !117, metadata !89), !dbg !118
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !119, metadata !89), !dbg !120
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !121
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 2, !dbg !123
  %1 = load i32, i32* %check, align 8, !dbg !123
  %cmp = icmp ugt i32 %1, 15, !dbg !124
  br i1 %cmp, label %if.then, label %if.end, !dbg !125

if.then:                                          ; preds = %entry
  store i1 true, i1* %retval, align 1, !dbg !126
  br label %return, !dbg !126

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %out.addr, align 8, !dbg !127
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !127
  store i8 0, i8* %arrayidx, align 1, !dbg !128
  %3 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !129
  %check1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %3, i32 0, i32 2, !dbg !130
  %4 = load i32, i32* %check1, align 8, !dbg !130
  %conv = trunc i32 %4 to i8, !dbg !129
  %5 = load i8*, i8** %out.addr, align 8, !dbg !131
  %arrayidx2 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !131
  store i8 %conv, i8* %arrayidx2, align 1, !dbg !132
  store i1 false, i1* %retval, align 1, !dbg !133
  br label %return, !dbg !133

return:                                           ; preds = %if.end, %if.then
  %6 = load i1, i1* %retval, align 1, !dbg !134
  ret i1 %6, !dbg !134
}

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @write32ne(i8* %buf, i32 %num) #4 !dbg !77 {
entry:
  %buf.addr = alloca i8*, align 8
  %num.addr = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !135, metadata !89), !dbg !136
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !137, metadata !89), !dbg !138
  %0 = load i32, i32* %num.addr, align 4, !dbg !139
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !140
  %2 = bitcast i8* %1 to i32*, !dbg !141
  store i32 %0, i32* %2, align 4, !dbg !142
  ret void, !dbg !143
}

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_footer_encode(%struct.lzma_stream_flags* %options, i8* %out) #0 !dbg !72 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  %out.addr = alloca i8*, align 8
  %crc = alloca i32, align 4
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !144, metadata !89), !dbg !145
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !146, metadata !89), !dbg !147
  call void @llvm.dbg.declare(metadata i32* %crc, metadata !148, metadata !89), !dbg !149
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !150
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 0, !dbg !152
  %1 = load i32, i32* %version, align 8, !dbg !152
  %cmp = icmp ne i32 %1, 0, !dbg !153
  br i1 %cmp, label %if.then, label %if.end, !dbg !154

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !155
  br label %return, !dbg !155

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !156
  %call = call zeroext i1 @is_backward_size_valid(%struct.lzma_stream_flags* %2), !dbg !158
  br i1 %call, label %if.end2, label %if.then1, !dbg !159

if.then1:                                         ; preds = %if.end
  store i32 11, i32* %retval, align 4, !dbg !160
  br label %return, !dbg !160

if.end2:                                          ; preds = %if.end
  %3 = load i8*, i8** %out.addr, align 8, !dbg !161
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !161
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !161
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %4, i32 0, i32 1, !dbg !161
  %5 = load i64, i64* %backward_size, align 8, !dbg !161
  %div = udiv i64 %5, 4, !dbg !161
  %sub = sub i64 %div, 1, !dbg !161
  %conv = trunc i64 %sub to i32, !dbg !161
  call void @write32ne(i8* %add.ptr, i32 %conv), !dbg !161
  %6 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !162
  %7 = load i8*, i8** %out.addr, align 8, !dbg !164
  %add.ptr3 = getelementptr inbounds i8, i8* %7, i64 8, !dbg !165
  %call4 = call zeroext i1 @stream_flags_encode(%struct.lzma_stream_flags* %6, i8* %add.ptr3), !dbg !166
  br i1 %call4, label %if.then5, label %if.end6, !dbg !167

if.then5:                                         ; preds = %if.end2
  store i32 11, i32* %retval, align 4, !dbg !168
  br label %return, !dbg !168

if.end6:                                          ; preds = %if.end2
  %8 = load i8*, i8** %out.addr, align 8, !dbg !169
  %add.ptr7 = getelementptr inbounds i8, i8* %8, i64 4, !dbg !170
  %call8 = call i32 @lzma_crc32(i8* %add.ptr7, i64 6, i32 0) #5, !dbg !171
  store i32 %call8, i32* %crc, align 4, !dbg !172
  %9 = load i8*, i8** %out.addr, align 8, !dbg !173
  %10 = load i32, i32* %crc, align 4, !dbg !173
  call void @write32ne(i8* %9, i32 %10), !dbg !173
  %11 = load i8*, i8** %out.addr, align 8, !dbg !174
  %add.ptr9 = getelementptr inbounds i8, i8* %11, i64 8, !dbg !175
  %add.ptr10 = getelementptr inbounds i8, i8* %add.ptr9, i64 2, !dbg !176
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr10, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @lzma_footer_magic, i32 0, i32 0), i64 2, i32 1, i1 false), !dbg !177
  store i32 0, i32* %retval, align 4, !dbg !178
  br label %return, !dbg !178

return:                                           ; preds = %if.end6, %if.then5, %if.then1, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !179
  ret i32 %12, !dbg !179
}

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @is_backward_size_valid(%struct.lzma_stream_flags* %options) #4 !dbg !81 {
entry:
  %options.addr = alloca %struct.lzma_stream_flags*, align 8
  store %struct.lzma_stream_flags* %options, %struct.lzma_stream_flags** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %options.addr, metadata !180, metadata !89), !dbg !181
  %0 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !182
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %0, i32 0, i32 1, !dbg !183
  %1 = load i64, i64* %backward_size, align 8, !dbg !183
  %cmp = icmp uge i64 %1, 4, !dbg !184
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !185

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !186
  %backward_size1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %2, i32 0, i32 1, !dbg !188
  %3 = load i64, i64* %backward_size1, align 8, !dbg !188
  %cmp2 = icmp ule i64 %3, 17179869184, !dbg !189
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !190

land.rhs:                                         ; preds = %land.lhs.true
  %4 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %options.addr, align 8, !dbg !191
  %backward_size3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %4, i32 0, i32 1, !dbg !192
  %5 = load i64, i64* %backward_size3, align 8, !dbg !192
  %and = and i64 %5, 3, !dbg !193
  %cmp4 = icmp eq i64 %and, 0, !dbg !194
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %entry
  %6 = phi i1 [ false, %land.lhs.true ], [ false, %entry ], [ %cmp4, %land.rhs ]
  ret i1 %6, !dbg !195
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!85, !86}
!llvm.ident = !{!87}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !33)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!28 = !{!29, !31, !32}
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !30, line: 51, baseType: !31)
!30 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!31 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!33 = !{!34, !72, !73, !77, !81}
!34 = distinct !DISubprogram(name: "lzma_stream_header_encode", scope: !1, file: !1, line: 30, type: !35, isLocal: false, isDefinition: true, scopeLine: 31, flags: DIFlagPrototyped, isOptimized: false, variables: !71)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !69}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !40)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !41, line: 105, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 33, size: 448, align: 64, elements: !43)
!43 = !{!44, !45, !50, !52, !54, !55, !56, !57, !60, !61, !62, !63, !64, !65, !66, !67, !68}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !42, file: !41, line: 51, baseType: !29, size: 32, align: 32)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !42, file: !41, line: 69, baseType: !46, size: 64, align: 64, offset: 64)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !47, line: 63, baseType: !48)
!47 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !30, line: 55, baseType: !49)
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
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !42, file: !41, line: 102, baseType: !29, size: 32, align: 32, offset: 352)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !42, file: !41, line: 103, baseType: !29, size: 32, align: 32, offset: 384)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !30, line: 48, baseType: !59)
!71 = !{}
!72 = distinct !DISubprogram(name: "lzma_stream_footer_encode", scope: !1, file: !1, line: 59, type: !35, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !71)
!73 = distinct !DISubprogram(name: "stream_flags_encode", scope: !1, file: !1, line: 17, type: !74, isLocal: true, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !71)
!74 = !DISubroutineType(types: !75)
!75 = !{!76, !38, !69}
!76 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!77 = distinct !DISubprogram(name: "write32ne", scope: !78, file: !78, line: 255, type: !79, isLocal: true, isDefinition: true, scopeLine: 256, flags: DIFlagPrototyped, isOptimized: false, variables: !71)
!78 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!79 = !DISubroutineType(types: !80)
!80 = !{null, !69, !29}
!81 = distinct !DISubprogram(name: "is_backward_size_valid", scope: !82, file: !82, line: 26, type: !83, isLocal: true, isDefinition: true, scopeLine: 27, flags: DIFlagPrototyped, isOptimized: false, variables: !71)
!82 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_flags_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!83 = !DISubroutineType(types: !84)
!84 = !{!76, !38}
!85 = !{i32 2, !"Dwarf Version", i32 4}
!86 = !{i32 2, !"Debug Info Version", i32 3}
!87 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!88 = !DILocalVariable(name: "options", arg: 1, scope: !34, file: !1, line: 30, type: !38)
!89 = !DIExpression()
!90 = !DILocation(line: 30, column: 52, scope: !34)
!91 = !DILocalVariable(name: "out", arg: 2, scope: !34, file: !1, line: 30, type: !69)
!92 = !DILocation(line: 30, column: 70, scope: !34)
!93 = !DILocalVariable(name: "crc", scope: !34, file: !1, line: 32, type: !29)
!94 = !DILocation(line: 32, column: 11, scope: !34)
!95 = !DILocation(line: 37, column: 6, scope: !96)
!96 = distinct !DILexicalBlock(scope: !34, file: !1, line: 37, column: 6)
!97 = !DILocation(line: 37, column: 15, scope: !96)
!98 = !DILocation(line: 37, column: 23, scope: !96)
!99 = !DILocation(line: 37, column: 6, scope: !34)
!100 = !DILocation(line: 38, column: 3, scope: !96)
!101 = !DILocation(line: 41, column: 9, scope: !34)
!102 = !DILocation(line: 41, column: 2, scope: !34)
!103 = !DILocation(line: 44, column: 26, scope: !104)
!104 = distinct !DILexicalBlock(scope: !34, file: !1, line: 44, column: 6)
!105 = !DILocation(line: 44, column: 35, scope: !104)
!106 = !DILocation(line: 44, column: 39, scope: !104)
!107 = !DILocation(line: 44, column: 6, scope: !104)
!108 = !DILocation(line: 44, column: 6, scope: !34)
!109 = !DILocation(line: 45, column: 3, scope: !104)
!110 = !DILocation(line: 48, column: 19, scope: !34)
!111 = !DILocation(line: 48, column: 23, scope: !34)
!112 = !DILocation(line: 48, column: 8, scope: !34)
!113 = !DILocation(line: 48, column: 6, scope: !34)
!114 = !DILocation(line: 51, column: 2, scope: !34)
!115 = !DILocation(line: 54, column: 2, scope: !34)
!116 = !DILocation(line: 55, column: 1, scope: !34)
!117 = !DILocalVariable(name: "options", arg: 1, scope: !73, file: !1, line: 17, type: !38)
!118 = !DILocation(line: 17, column: 46, scope: !73)
!119 = !DILocalVariable(name: "out", arg: 2, scope: !73, file: !1, line: 17, type: !69)
!120 = !DILocation(line: 17, column: 64, scope: !73)
!121 = !DILocation(line: 19, column: 21, scope: !122)
!122 = distinct !DILexicalBlock(scope: !73, file: !1, line: 19, column: 6)
!123 = !DILocation(line: 19, column: 30, scope: !122)
!124 = !DILocation(line: 19, column: 37, scope: !122)
!125 = !DILocation(line: 19, column: 6, scope: !73)
!126 = !DILocation(line: 20, column: 3, scope: !122)
!127 = !DILocation(line: 22, column: 2, scope: !73)
!128 = !DILocation(line: 22, column: 9, scope: !73)
!129 = !DILocation(line: 23, column: 11, scope: !73)
!130 = !DILocation(line: 23, column: 20, scope: !73)
!131 = !DILocation(line: 23, column: 2, scope: !73)
!132 = !DILocation(line: 23, column: 9, scope: !73)
!133 = !DILocation(line: 25, column: 2, scope: !73)
!134 = !DILocation(line: 26, column: 1, scope: !73)
!135 = !DILocalVariable(name: "buf", arg: 1, scope: !77, file: !78, line: 255, type: !69)
!136 = !DILocation(line: 255, column: 20, scope: !77)
!137 = !DILocalVariable(name: "num", arg: 2, scope: !77, file: !78, line: 255, type: !29)
!138 = !DILocation(line: 255, column: 34, scope: !77)
!139 = !DILocation(line: 257, column: 21, scope: !77)
!140 = !DILocation(line: 257, column: 15, scope: !77)
!141 = !DILocation(line: 257, column: 2, scope: !77)
!142 = !DILocation(line: 257, column: 19, scope: !77)
!143 = !DILocation(line: 258, column: 2, scope: !77)
!144 = !DILocalVariable(name: "options", arg: 1, scope: !72, file: !1, line: 59, type: !38)
!145 = !DILocation(line: 59, column: 52, scope: !72)
!146 = !DILocalVariable(name: "out", arg: 2, scope: !72, file: !1, line: 59, type: !69)
!147 = !DILocation(line: 59, column: 70, scope: !72)
!148 = !DILocalVariable(name: "crc", scope: !72, file: !1, line: 61, type: !29)
!149 = !DILocation(line: 61, column: 11, scope: !72)
!150 = !DILocation(line: 66, column: 6, scope: !151)
!151 = distinct !DILexicalBlock(scope: !72, file: !1, line: 66, column: 6)
!152 = !DILocation(line: 66, column: 15, scope: !151)
!153 = !DILocation(line: 66, column: 23, scope: !151)
!154 = !DILocation(line: 66, column: 6, scope: !72)
!155 = !DILocation(line: 67, column: 3, scope: !151)
!156 = !DILocation(line: 70, column: 30, scope: !157)
!157 = distinct !DILexicalBlock(scope: !72, file: !1, line: 70, column: 6)
!158 = !DILocation(line: 70, column: 7, scope: !157)
!159 = !DILocation(line: 70, column: 6, scope: !72)
!160 = !DILocation(line: 71, column: 3, scope: !157)
!161 = !DILocation(line: 73, column: 2, scope: !72)
!162 = !DILocation(line: 76, column: 26, scope: !163)
!163 = distinct !DILexicalBlock(scope: !72, file: !1, line: 76, column: 6)
!164 = !DILocation(line: 76, column: 35, scope: !163)
!165 = !DILocation(line: 76, column: 39, scope: !163)
!166 = !DILocation(line: 76, column: 6, scope: !163)
!167 = !DILocation(line: 76, column: 6, scope: !72)
!168 = !DILocation(line: 77, column: 3, scope: !163)
!169 = !DILocation(line: 81, column: 4, scope: !72)
!170 = !DILocation(line: 81, column: 8, scope: !72)
!171 = !DILocation(line: 80, column: 8, scope: !72)
!172 = !DILocation(line: 80, column: 6, scope: !72)
!173 = !DILocation(line: 83, column: 2, scope: !72)
!174 = !DILocation(line: 86, column: 9, scope: !72)
!175 = !DILocation(line: 86, column: 13, scope: !72)
!176 = !DILocation(line: 86, column: 21, scope: !72)
!177 = !DILocation(line: 86, column: 2, scope: !72)
!178 = !DILocation(line: 89, column: 2, scope: !72)
!179 = !DILocation(line: 90, column: 1, scope: !72)
!180 = !DILocalVariable(name: "options", arg: 1, scope: !81, file: !82, line: 26, type: !38)
!181 = !DILocation(line: 26, column: 49, scope: !81)
!182 = !DILocation(line: 28, column: 9, scope: !81)
!183 = !DILocation(line: 28, column: 18, scope: !81)
!184 = !DILocation(line: 28, column: 32, scope: !81)
!185 = !DILocation(line: 29, column: 4, scope: !81)
!186 = !DILocation(line: 29, column: 7, scope: !187)
!187 = !DILexicalBlockFile(scope: !81, file: !82, discriminator: 1)
!188 = !DILocation(line: 29, column: 16, scope: !187)
!189 = !DILocation(line: 29, column: 30, scope: !187)
!190 = !DILocation(line: 30, column: 4, scope: !81)
!191 = !DILocation(line: 30, column: 8, scope: !187)
!192 = !DILocation(line: 30, column: 17, scope: !187)
!193 = !DILocation(line: 30, column: 31, scope: !187)
!194 = !DILocation(line: 30, column: 36, scope: !187)
!195 = !DILocation(line: 28, column: 2, scope: !187)
