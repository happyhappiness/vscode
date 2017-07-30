; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/arm.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i8, i8, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, %struct.lzma_simple_s*, i32, i64, i64, i64, i64, [0 x i8] }
%struct.lzma_simple_s = type opaque
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_arm_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !36 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !158, metadata !159), !dbg !160
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !161, metadata !159), !dbg !162
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !163, metadata !159), !dbg !164
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !165
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !166
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !167
  %call = call i32 @arm_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i1 zeroext true), !dbg !168
  ret i32 %call, !dbg !169
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @arm_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters, i1 zeroext %is_encoder) #0 !dbg !151 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %is_encoder.addr = alloca i8, align 1
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !170, metadata !159), !dbg !171
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !172, metadata !159), !dbg !173
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !174, metadata !159), !dbg !175
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !176, metadata !159), !dbg !177
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !178
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !179
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !180
  %3 = load i8, i8* %is_encoder.addr, align 1, !dbg !181
  %tobool = trunc i8 %3 to i1, !dbg !181
  %call = call i32 @lzma_simple_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)* @arm_code, i64 0, i64 4, i32 4, i1 zeroext %tobool), !dbg !182
  ret i32 %call, !dbg !183
}

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_arm_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !150 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !184, metadata !159), !dbg !185
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !186, metadata !159), !dbg !187
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !188, metadata !159), !dbg !189
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !190
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !191
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !192
  %call = call i32 @arm_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i1 zeroext false), !dbg !193
  ret i32 %call, !dbg !194
}

declare i32 @lzma_simple_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, i64, i64, i32, i1 zeroext) #2

; Function Attrs: nounwind uwtable
define internal i64 @arm_code(%struct.lzma_simple_s* %simple, i32 %now_pos, i1 zeroext %is_encoder, i8* %buffer, i64 %size) #0 !dbg !154 {
entry:
  %simple.addr = alloca %struct.lzma_simple_s*, align 8
  %now_pos.addr = alloca i32, align 4
  %is_encoder.addr = alloca i8, align 1
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %dest = alloca i32, align 4
  %src = alloca i32, align 4
  store %struct.lzma_simple_s* %simple, %struct.lzma_simple_s** %simple.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_simple_s** %simple.addr, metadata !195, metadata !159), !dbg !196
  store i32 %now_pos, i32* %now_pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %now_pos.addr, metadata !197, metadata !159), !dbg !198
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !199, metadata !159), !dbg !200
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !201, metadata !159), !dbg !202
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !203, metadata !159), !dbg !204
  call void @llvm.dbg.declare(metadata i64* %i, metadata !205, metadata !159), !dbg !206
  store i64 0, i64* %i, align 8, !dbg !207
  br label %for.cond, !dbg !209

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !210
  %add = add i64 %0, 4, !dbg !213
  %1 = load i64, i64* %size.addr, align 8, !dbg !214
  %cmp = icmp ule i64 %add, %1, !dbg !215
  br i1 %cmp, label %for.body, label %for.end, !dbg !216

for.body:                                         ; preds = %for.cond
  %2 = load i64, i64* %i, align 8, !dbg !217
  %add1 = add i64 %2, 3, !dbg !220
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !221
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %add1, !dbg !221
  %4 = load i8, i8* %arrayidx, align 1, !dbg !221
  %conv = zext i8 %4 to i32, !dbg !221
  %cmp2 = icmp eq i32 %conv, 235, !dbg !222
  br i1 %cmp2, label %if.then, label %if.end35, !dbg !223

if.then:                                          ; preds = %for.body
  call void @llvm.dbg.declare(metadata i32* %dest, metadata !224, metadata !159), !dbg !226
  call void @llvm.dbg.declare(metadata i32* %src, metadata !227, metadata !159), !dbg !228
  %5 = load i64, i64* %i, align 8, !dbg !229
  %add4 = add i64 %5, 2, !dbg !230
  %6 = load i8*, i8** %buffer.addr, align 8, !dbg !231
  %arrayidx5 = getelementptr inbounds i8, i8* %6, i64 %add4, !dbg !231
  %7 = load i8, i8* %arrayidx5, align 1, !dbg !231
  %conv6 = zext i8 %7 to i32, !dbg !231
  %shl = shl i32 %conv6, 16, !dbg !232
  %8 = load i64, i64* %i, align 8, !dbg !233
  %add7 = add i64 %8, 1, !dbg !234
  %9 = load i8*, i8** %buffer.addr, align 8, !dbg !235
  %arrayidx8 = getelementptr inbounds i8, i8* %9, i64 %add7, !dbg !235
  %10 = load i8, i8* %arrayidx8, align 1, !dbg !235
  %conv9 = zext i8 %10 to i32, !dbg !235
  %shl10 = shl i32 %conv9, 8, !dbg !236
  %or = or i32 %shl, %shl10, !dbg !237
  %11 = load i64, i64* %i, align 8, !dbg !238
  %add11 = add i64 %11, 0, !dbg !239
  %12 = load i8*, i8** %buffer.addr, align 8, !dbg !240
  %arrayidx12 = getelementptr inbounds i8, i8* %12, i64 %add11, !dbg !240
  %13 = load i8, i8* %arrayidx12, align 1, !dbg !240
  %conv13 = zext i8 %13 to i32, !dbg !241
  %or14 = or i32 %or, %conv13, !dbg !242
  store i32 %or14, i32* %src, align 4, !dbg !228
  %14 = load i32, i32* %src, align 4, !dbg !243
  %shl15 = shl i32 %14, 2, !dbg !243
  store i32 %shl15, i32* %src, align 4, !dbg !243
  %15 = load i8, i8* %is_encoder.addr, align 1, !dbg !244
  %tobool = trunc i8 %15 to i1, !dbg !244
  br i1 %tobool, label %if.then16, label %if.else, !dbg !246

if.then16:                                        ; preds = %if.then
  %16 = load i32, i32* %now_pos.addr, align 4, !dbg !247
  %17 = load i64, i64* %i, align 8, !dbg !248
  %conv17 = trunc i64 %17 to i32, !dbg !249
  %add18 = add i32 %16, %conv17, !dbg !250
  %add19 = add i32 %add18, 8, !dbg !251
  %18 = load i32, i32* %src, align 4, !dbg !252
  %add20 = add i32 %add19, %18, !dbg !253
  store i32 %add20, i32* %dest, align 4, !dbg !254
  br label %if.end, !dbg !255

if.else:                                          ; preds = %if.then
  %19 = load i32, i32* %src, align 4, !dbg !256
  %20 = load i32, i32* %now_pos.addr, align 4, !dbg !257
  %21 = load i64, i64* %i, align 8, !dbg !258
  %conv21 = trunc i64 %21 to i32, !dbg !259
  %add22 = add i32 %20, %conv21, !dbg !260
  %add23 = add i32 %add22, 8, !dbg !261
  %sub = sub i32 %19, %add23, !dbg !262
  store i32 %sub, i32* %dest, align 4, !dbg !263
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then16
  %22 = load i32, i32* %dest, align 4, !dbg !264
  %shr = lshr i32 %22, 2, !dbg !264
  store i32 %shr, i32* %dest, align 4, !dbg !264
  %23 = load i32, i32* %dest, align 4, !dbg !265
  %shr24 = lshr i32 %23, 16, !dbg !266
  %conv25 = trunc i32 %shr24 to i8, !dbg !267
  %24 = load i64, i64* %i, align 8, !dbg !268
  %add26 = add i64 %24, 2, !dbg !269
  %25 = load i8*, i8** %buffer.addr, align 8, !dbg !270
  %arrayidx27 = getelementptr inbounds i8, i8* %25, i64 %add26, !dbg !270
  store i8 %conv25, i8* %arrayidx27, align 1, !dbg !271
  %26 = load i32, i32* %dest, align 4, !dbg !272
  %shr28 = lshr i32 %26, 8, !dbg !273
  %conv29 = trunc i32 %shr28 to i8, !dbg !274
  %27 = load i64, i64* %i, align 8, !dbg !275
  %add30 = add i64 %27, 1, !dbg !276
  %28 = load i8*, i8** %buffer.addr, align 8, !dbg !277
  %arrayidx31 = getelementptr inbounds i8, i8* %28, i64 %add30, !dbg !277
  store i8 %conv29, i8* %arrayidx31, align 1, !dbg !278
  %29 = load i32, i32* %dest, align 4, !dbg !279
  %conv32 = trunc i32 %29 to i8, !dbg !279
  %30 = load i64, i64* %i, align 8, !dbg !280
  %add33 = add i64 %30, 0, !dbg !281
  %31 = load i8*, i8** %buffer.addr, align 8, !dbg !282
  %arrayidx34 = getelementptr inbounds i8, i8* %31, i64 %add33, !dbg !282
  store i8 %conv32, i8* %arrayidx34, align 1, !dbg !283
  br label %if.end35, !dbg !284

if.end35:                                         ; preds = %if.end, %for.body
  br label %for.inc, !dbg !285

for.inc:                                          ; preds = %if.end35
  %32 = load i64, i64* %i, align 8, !dbg !286
  %add36 = add i64 %32, 4, !dbg !286
  store i64 %add36, i64* %i, align 8, !dbg !286
  br label %for.cond, !dbg !288

for.end:                                          ; preds = %for.cond
  %33 = load i64, i64* %i, align 8, !dbg !289
  ret i64 %33, !dbg !290
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!155, !156}
!llvm.ident = !{!157}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !35)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/arm.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !{!32}
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!35 = !{!36, !150, !151, !154}
!36 = distinct !DISubprogram(name: "lzma_simple_arm_encoder_init", scope: !1, file: !1, line: 57, type: !37, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!37 = !DISubroutineType(types: !38)
!38 = !{!39, !40, !89, !139}
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !42, line: 75, baseType: !43)
!42 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!43 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !42, line: 119, size: 512, align: 64, elements: !44)
!44 = !{!45, !78, !82, !84, !110, !115, !122, !127}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !43, file: !42, line: 121, baseType: !46, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !42, line: 73, baseType: !48)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !49, line: 21, size: 1024, align: 64, elements: !50)
!49 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!50 = !{!51, !52, !54, !55, !68, !69, !70, !71, !72, !73, !74}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !48, file: !49, line: 23, baseType: !41, size: 512, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "end_was_reached", scope: !48, file: !49, line: 26, baseType: !53, size: 8, align: 8, offset: 512)
!53 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "is_encoder", scope: !48, file: !49, line: 32, baseType: !53, size: 8, align: 8, offset: 520)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !48, file: !49, line: 36, baseType: !56, size: 64, align: 64, offset: 576)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{!59, !62, !32, !53, !65, !59}
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !60, line: 62, baseType: !61)
!60 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_simple", file: !49, line: 19, baseType: !64)
!64 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_simple_s", file: !49, line: 19, flags: DIFlagFwdDecl)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !33, line: 48, baseType: !67)
!67 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "simple", scope: !48, file: !49, line: 41, baseType: !62, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "now_pos", scope: !48, file: !49, line: 46, baseType: !32, size: 32, align: 32, offset: 704)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "allocated", scope: !48, file: !49, line: 49, baseType: !59, size: 64, align: 64, offset: 768)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !48, file: !49, line: 53, baseType: !59, size: 64, align: 64, offset: 832)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "filtered", scope: !48, file: !49, line: 57, baseType: !59, size: 64, align: 64, offset: 896)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !48, file: !49, line: 61, baseType: !59, size: 64, align: 64, offset: 960)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !48, file: !49, line: 64, baseType: !75, offset: 1024)
!75 = !DICompositeType(tag: DW_TAG_array_type, baseType: !66, align: 8, elements: !76)
!76 = !{!77}
!77 = !DISubrange(count: -1)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !43, file: !42, line: 125, baseType: !79, size: 64, align: 64, offset: 64)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !80, line: 63, baseType: !81)
!80 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !33, line: 55, baseType: !61)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !43, file: !42, line: 131, baseType: !83, size: 64, align: 64, offset: 128)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !33, line: 122, baseType: !61)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !43, file: !42, line: 134, baseType: !85, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !42, line: 89, baseType: !86)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{!39, !46, !89, !103, !106, !59, !108, !106, !59, !109}
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !91)
!91 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !92)
!92 = !{!93, !98, !102}
!93 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !91, file: !4, line: 376, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!95 = !DISubroutineType(types: !96)
!96 = !{!97, !97, !59, !59}
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !91, file: !4, line: 390, baseType: !99, size: 64, align: 64, offset: 64)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DISubroutineType(types: !101)
!101 = !{null, !97, !97}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !91, file: !4, line: 401, baseType: !97, size: 64, align: 64, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !104)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !66)
!106 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !107)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !65)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !43, file: !42, line: 139, baseType: !111, size: 64, align: 64, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !42, line: 97, baseType: !112)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{null, !46, !89}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !43, file: !42, line: 143, baseType: !116, size: 64, align: 64, offset: 320)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !120}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !47)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !43, file: !42, line: 147, baseType: !123, size: 64, align: 64, offset: 384)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{!39, !46, !126, !126, !81}
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !43, file: !42, line: 152, baseType: !128, size: 64, align: 64, offset: 448)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DISubroutineType(types: !130)
!130 = !{!39, !46, !89, !131, !131}
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !133)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !134, line: 65, baseType: !135)
!134 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!135 = !DICompositeType(tag: DW_TAG_structure_type, file: !134, line: 43, size: 128, align: 64, elements: !136)
!136 = !{!137, !138}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !135, file: !134, line: 54, baseType: !79, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !135, file: !134, line: 63, baseType: !97, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !141)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !42, line: 77, baseType: !142)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !42, line: 104, size: 192, align: 64, elements: !143)
!143 = !{!144, !145, !148}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !142, file: !42, line: 107, baseType: !79, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !142, file: !42, line: 111, baseType: !146, size: 64, align: 64, offset: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !42, line: 81, baseType: !147)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !142, file: !42, line: 114, baseType: !97, size: 64, align: 64, offset: 128)
!149 = !{}
!150 = distinct !DISubprogram(name: "lzma_simple_arm_decoder_init", scope: !1, file: !1, line: 65, type: !37, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!151 = distinct !DISubprogram(name: "arm_coder_init", scope: !1, file: !1, line: 48, type: !152, isLocal: true, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!152 = !DISubroutineType(types: !153)
!153 = !{!39, !40, !89, !139, !53}
!154 = distinct !DISubprogram(name: "arm_code", scope: !1, file: !1, line: 18, type: !57, isLocal: true, isDefinition: true, scopeLine: 21, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!155 = !{i32 2, !"Dwarf Version", i32 4}
!156 = !{i32 2, !"Debug Info Version", i32 3}
!157 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!158 = !DILocalVariable(name: "next", arg: 1, scope: !36, file: !1, line: 57, type: !40)
!159 = !DIExpression()
!160 = !DILocation(line: 57, column: 47, scope: !36)
!161 = !DILocalVariable(name: "allocator", arg: 2, scope: !36, file: !1, line: 57, type: !89)
!162 = !DILocation(line: 57, column: 69, scope: !36)
!163 = !DILocalVariable(name: "filters", arg: 3, scope: !36, file: !1, line: 58, type: !139)
!164 = !DILocation(line: 58, column: 27, scope: !36)
!165 = !DILocation(line: 60, column: 24, scope: !36)
!166 = !DILocation(line: 60, column: 30, scope: !36)
!167 = !DILocation(line: 60, column: 41, scope: !36)
!168 = !DILocation(line: 60, column: 9, scope: !36)
!169 = !DILocation(line: 60, column: 2, scope: !36)
!170 = !DILocalVariable(name: "next", arg: 1, scope: !151, file: !1, line: 48, type: !40)
!171 = !DILocation(line: 48, column: 33, scope: !151)
!172 = !DILocalVariable(name: "allocator", arg: 2, scope: !151, file: !1, line: 48, type: !89)
!173 = !DILocation(line: 48, column: 55, scope: !151)
!174 = !DILocalVariable(name: "filters", arg: 3, scope: !151, file: !1, line: 49, type: !139)
!175 = !DILocation(line: 49, column: 27, scope: !151)
!176 = !DILocalVariable(name: "is_encoder", arg: 4, scope: !151, file: !1, line: 49, type: !53)
!177 = !DILocation(line: 49, column: 41, scope: !151)
!178 = !DILocation(line: 51, column: 32, scope: !151)
!179 = !DILocation(line: 51, column: 38, scope: !151)
!180 = !DILocation(line: 51, column: 49, scope: !151)
!181 = !DILocation(line: 52, column: 24, scope: !151)
!182 = !DILocation(line: 51, column: 9, scope: !151)
!183 = !DILocation(line: 51, column: 2, scope: !151)
!184 = !DILocalVariable(name: "next", arg: 1, scope: !150, file: !1, line: 65, type: !40)
!185 = !DILocation(line: 65, column: 47, scope: !150)
!186 = !DILocalVariable(name: "allocator", arg: 2, scope: !150, file: !1, line: 65, type: !89)
!187 = !DILocation(line: 65, column: 69, scope: !150)
!188 = !DILocalVariable(name: "filters", arg: 3, scope: !150, file: !1, line: 66, type: !139)
!189 = !DILocation(line: 66, column: 27, scope: !150)
!190 = !DILocation(line: 68, column: 24, scope: !150)
!191 = !DILocation(line: 68, column: 30, scope: !150)
!192 = !DILocation(line: 68, column: 41, scope: !150)
!193 = !DILocation(line: 68, column: 9, scope: !150)
!194 = !DILocation(line: 68, column: 2, scope: !150)
!195 = !DILocalVariable(name: "simple", arg: 1, scope: !154, file: !1, line: 18, type: !62)
!196 = !DILocation(line: 18, column: 23, scope: !154)
!197 = !DILocalVariable(name: "now_pos", arg: 2, scope: !154, file: !1, line: 19, type: !32)
!198 = !DILocation(line: 19, column: 12, scope: !154)
!199 = !DILocalVariable(name: "is_encoder", arg: 3, scope: !154, file: !1, line: 19, type: !53)
!200 = !DILocation(line: 19, column: 26, scope: !154)
!201 = !DILocalVariable(name: "buffer", arg: 4, scope: !154, file: !1, line: 20, type: !65)
!202 = !DILocation(line: 20, column: 12, scope: !154)
!203 = !DILocalVariable(name: "size", arg: 5, scope: !154, file: !1, line: 20, type: !59)
!204 = !DILocation(line: 20, column: 27, scope: !154)
!205 = !DILocalVariable(name: "i", scope: !154, file: !1, line: 22, type: !59)
!206 = !DILocation(line: 22, column: 9, scope: !154)
!207 = !DILocation(line: 23, column: 9, scope: !208)
!208 = distinct !DILexicalBlock(scope: !154, file: !1, line: 23, column: 2)
!209 = !DILocation(line: 23, column: 7, scope: !208)
!210 = !DILocation(line: 23, column: 14, scope: !211)
!211 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 1)
!212 = distinct !DILexicalBlock(scope: !208, file: !1, line: 23, column: 2)
!213 = !DILocation(line: 23, column: 16, scope: !211)
!214 = !DILocation(line: 23, column: 23, scope: !211)
!215 = !DILocation(line: 23, column: 20, scope: !211)
!216 = !DILocation(line: 23, column: 2, scope: !211)
!217 = !DILocation(line: 24, column: 14, scope: !218)
!218 = distinct !DILexicalBlock(scope: !219, file: !1, line: 24, column: 7)
!219 = distinct !DILexicalBlock(scope: !212, file: !1, line: 23, column: 37)
!220 = !DILocation(line: 24, column: 16, scope: !218)
!221 = !DILocation(line: 24, column: 7, scope: !218)
!222 = !DILocation(line: 24, column: 21, scope: !218)
!223 = !DILocation(line: 24, column: 7, scope: !219)
!224 = !DILocalVariable(name: "dest", scope: !225, file: !1, line: 25, type: !32)
!225 = distinct !DILexicalBlock(scope: !218, file: !1, line: 24, column: 30)
!226 = !DILocation(line: 25, column: 13, scope: !225)
!227 = !DILocalVariable(name: "src", scope: !225, file: !1, line: 26, type: !32)
!228 = !DILocation(line: 26, column: 13, scope: !225)
!229 = !DILocation(line: 26, column: 27, scope: !225)
!230 = !DILocation(line: 26, column: 29, scope: !225)
!231 = !DILocation(line: 26, column: 20, scope: !225)
!232 = !DILocation(line: 26, column: 34, scope: !225)
!233 = !DILocation(line: 27, column: 16, scope: !225)
!234 = !DILocation(line: 27, column: 18, scope: !225)
!235 = !DILocation(line: 27, column: 9, scope: !225)
!236 = !DILocation(line: 27, column: 23, scope: !225)
!237 = !DILocation(line: 27, column: 6, scope: !225)
!238 = !DILocation(line: 28, column: 16, scope: !225)
!239 = !DILocation(line: 28, column: 18, scope: !225)
!240 = !DILocation(line: 28, column: 9, scope: !225)
!241 = !DILocation(line: 28, column: 8, scope: !225)
!242 = !DILocation(line: 28, column: 6, scope: !225)
!243 = !DILocation(line: 29, column: 8, scope: !225)
!244 = !DILocation(line: 31, column: 8, scope: !245)
!245 = distinct !DILexicalBlock(scope: !225, file: !1, line: 31, column: 8)
!246 = !DILocation(line: 31, column: 8, scope: !225)
!247 = !DILocation(line: 32, column: 12, scope: !245)
!248 = !DILocation(line: 32, column: 33, scope: !245)
!249 = !DILocation(line: 32, column: 22, scope: !245)
!250 = !DILocation(line: 32, column: 20, scope: !245)
!251 = !DILocation(line: 32, column: 36, scope: !245)
!252 = !DILocation(line: 32, column: 42, scope: !245)
!253 = !DILocation(line: 32, column: 40, scope: !245)
!254 = !DILocation(line: 32, column: 10, scope: !245)
!255 = !DILocation(line: 32, column: 5, scope: !245)
!256 = !DILocation(line: 34, column: 12, scope: !245)
!257 = !DILocation(line: 34, column: 19, scope: !245)
!258 = !DILocation(line: 34, column: 40, scope: !245)
!259 = !DILocation(line: 34, column: 29, scope: !245)
!260 = !DILocation(line: 34, column: 27, scope: !245)
!261 = !DILocation(line: 34, column: 43, scope: !245)
!262 = !DILocation(line: 34, column: 16, scope: !245)
!263 = !DILocation(line: 34, column: 10, scope: !245)
!264 = !DILocation(line: 36, column: 9, scope: !225)
!265 = !DILocation(line: 37, column: 21, scope: !225)
!266 = !DILocation(line: 37, column: 26, scope: !225)
!267 = !DILocation(line: 37, column: 20, scope: !225)
!268 = !DILocation(line: 37, column: 11, scope: !225)
!269 = !DILocation(line: 37, column: 13, scope: !225)
!270 = !DILocation(line: 37, column: 4, scope: !225)
!271 = !DILocation(line: 37, column: 18, scope: !225)
!272 = !DILocation(line: 38, column: 21, scope: !225)
!273 = !DILocation(line: 38, column: 26, scope: !225)
!274 = !DILocation(line: 38, column: 20, scope: !225)
!275 = !DILocation(line: 38, column: 11, scope: !225)
!276 = !DILocation(line: 38, column: 13, scope: !225)
!277 = !DILocation(line: 38, column: 4, scope: !225)
!278 = !DILocation(line: 38, column: 18, scope: !225)
!279 = !DILocation(line: 39, column: 20, scope: !225)
!280 = !DILocation(line: 39, column: 11, scope: !225)
!281 = !DILocation(line: 39, column: 13, scope: !225)
!282 = !DILocation(line: 39, column: 4, scope: !225)
!283 = !DILocation(line: 39, column: 18, scope: !225)
!284 = !DILocation(line: 40, column: 3, scope: !225)
!285 = !DILocation(line: 41, column: 2, scope: !219)
!286 = !DILocation(line: 23, column: 31, scope: !287)
!287 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 2)
!288 = !DILocation(line: 23, column: 2, scope: !287)
!289 = !DILocation(line: 43, column: 9, scope: !154)
!290 = !DILocation(line: 43, column: 2, scope: !154)
