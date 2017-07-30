; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [43 x i8] c"*in_pos == in_size || *out_pos == out_size\00", align 1
@.str.1 = private unnamed_addr constant [92 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_decoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_block_buffer_decode = private unnamed_addr constant [130 x i8] c"lzma_ret lzma_block_buffer_decode(lzma_block *, lzma_allocator *, const uint8_t *, size_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_block_buffer_decode(%struct.lzma_block* %block, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !37 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %block_decoder = alloca %struct.lzma_next_coder_s, align 8
  %ret = alloca i32, align 4
  %in_start = alloca i64, align 8
  %out_start = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !166, metadata !167), !dbg !168
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !169, metadata !167), !dbg !170
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !171, metadata !167), !dbg !172
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !173, metadata !167), !dbg !174
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !175, metadata !167), !dbg !176
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !177, metadata !167), !dbg !178
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !179, metadata !167), !dbg !180
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !181, metadata !167), !dbg !182
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s* %block_decoder, metadata !183, metadata !167), !dbg !184
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !185, metadata !167), !dbg !186
  %0 = load i64*, i64** %in_pos.addr, align 8, !dbg !187
  %cmp = icmp eq i64* %0, null, !dbg !189
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !190

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %in.addr, align 8, !dbg !191
  %cmp1 = icmp eq i8* %1, null, !dbg !193
  br i1 %cmp1, label %land.lhs.true, label %lor.lhs.false3, !dbg !194

land.lhs.true:                                    ; preds = %lor.lhs.false
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !195
  %3 = load i64, i64* %2, align 8, !dbg !197
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !198
  %cmp2 = icmp ne i64 %3, %4, !dbg !199
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !200

lor.lhs.false3:                                   ; preds = %land.lhs.true, %lor.lhs.false
  %5 = load i64*, i64** %in_pos.addr, align 8, !dbg !201
  %6 = load i64, i64* %5, align 8, !dbg !202
  %7 = load i64, i64* %in_size.addr, align 8, !dbg !203
  %cmp4 = icmp ugt i64 %6, %7, !dbg !204
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !205

lor.lhs.false5:                                   ; preds = %lor.lhs.false3
  %8 = load i64*, i64** %out_pos.addr, align 8, !dbg !206
  %cmp6 = icmp eq i64* %8, null, !dbg !207
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !208

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %9 = load i8*, i8** %out.addr, align 8, !dbg !209
  %cmp8 = icmp eq i8* %9, null, !dbg !210
  br i1 %cmp8, label %land.lhs.true9, label %lor.lhs.false11, !dbg !211

land.lhs.true9:                                   ; preds = %lor.lhs.false7
  %10 = load i64*, i64** %out_pos.addr, align 8, !dbg !212
  %11 = load i64, i64* %10, align 8, !dbg !213
  %12 = load i64, i64* %out_size.addr, align 8, !dbg !214
  %cmp10 = icmp ne i64 %11, %12, !dbg !215
  br i1 %cmp10, label %if.then, label %lor.lhs.false11, !dbg !216

lor.lhs.false11:                                  ; preds = %land.lhs.true9, %lor.lhs.false7
  %13 = load i64*, i64** %out_pos.addr, align 8, !dbg !217
  %14 = load i64, i64* %13, align 8, !dbg !218
  %15 = load i64, i64* %out_size.addr, align 8, !dbg !219
  %cmp12 = icmp ugt i64 %14, %15, !dbg !220
  br i1 %cmp12, label %if.then, label %if.end, !dbg !221

if.then:                                          ; preds = %lor.lhs.false11, %land.lhs.true9, %lor.lhs.false5, %lor.lhs.false3, %land.lhs.true, %entry
  store i32 11, i32* %retval, align 4, !dbg !223
  br label %return, !dbg !223

if.end:                                           ; preds = %lor.lhs.false11
  %16 = bitcast %struct.lzma_next_coder_s* %block_decoder to i8*, !dbg !224
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !224
  %17 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !225
  %18 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !226
  %call = call i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s* %block_decoder, %struct.lzma_allocator* %17, %struct.lzma_block* %18), !dbg !227
  store i32 %call, i32* %ret, align 4, !dbg !228
  %19 = load i32, i32* %ret, align 4, !dbg !229
  %cmp13 = icmp eq i32 %19, 0, !dbg !231
  br i1 %cmp13, label %if.then14, label %if.end29, !dbg !232

if.then14:                                        ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !233, metadata !167), !dbg !236
  %20 = load i64*, i64** %in_pos.addr, align 8, !dbg !237
  %21 = load i64, i64* %20, align 8, !dbg !238
  store i64 %21, i64* %in_start, align 8, !dbg !236
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !239, metadata !167), !dbg !240
  %22 = load i64*, i64** %out_pos.addr, align 8, !dbg !241
  %23 = load i64, i64* %22, align 8, !dbg !242
  store i64 %23, i64* %out_start, align 8, !dbg !240
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_decoder, i32 0, i32 3, !dbg !243
  %24 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !243
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_decoder, i32 0, i32 0, !dbg !244
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !244
  %26 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !245
  %27 = load i8*, i8** %in.addr, align 8, !dbg !246
  %28 = load i64*, i64** %in_pos.addr, align 8, !dbg !247
  %29 = load i64, i64* %in_size.addr, align 8, !dbg !248
  %30 = load i8*, i8** %out.addr, align 8, !dbg !249
  %31 = load i64*, i64** %out_pos.addr, align 8, !dbg !250
  %32 = load i64, i64* %out_size.addr, align 8, !dbg !251
  %call15 = call i32 %24(%struct.lzma_coder_s* %25, %struct.lzma_allocator* %26, i8* %27, i64* %28, i64 %29, i8* %30, i64* %31, i64 %32, i32 3), !dbg !252
  store i32 %call15, i32* %ret, align 4, !dbg !253
  %33 = load i32, i32* %ret, align 4, !dbg !254
  %cmp16 = icmp eq i32 %33, 1, !dbg !256
  br i1 %cmp16, label %if.then17, label %if.else, !dbg !257

if.then17:                                        ; preds = %if.then14
  store i32 0, i32* %ret, align 4, !dbg !258
  br label %if.end28, !dbg !260

if.else:                                          ; preds = %if.then14
  %34 = load i32, i32* %ret, align 4, !dbg !261
  %cmp18 = icmp eq i32 %34, 0, !dbg !264
  br i1 %cmp18, label %if.then19, label %if.end27, !dbg !265

if.then19:                                        ; preds = %if.else
  %35 = load i64*, i64** %in_pos.addr, align 8, !dbg !266
  %36 = load i64, i64* %35, align 8, !dbg !266
  %37 = load i64, i64* %in_size.addr, align 8, !dbg !266
  %cmp20 = icmp eq i64 %36, %37, !dbg !266
  br i1 %cmp20, label %cond.true, label %lor.lhs.false21, !dbg !266

lor.lhs.false21:                                  ; preds = %if.then19
  %38 = load i64*, i64** %out_pos.addr, align 8, !dbg !268
  %39 = load i64, i64* %38, align 8, !dbg !268
  %40 = load i64, i64* %out_size.addr, align 8, !dbg !268
  %cmp22 = icmp eq i64 %39, %40, !dbg !268
  br i1 %cmp22, label %cond.true, label %cond.false, !dbg !268

cond.true:                                        ; preds = %lor.lhs.false21, %if.then19
  br label %cond.end, !dbg !270

cond.false:                                       ; preds = %lor.lhs.false21
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 52, i8* getelementptr inbounds ([130 x i8], [130 x i8]* @__PRETTY_FUNCTION__.lzma_block_buffer_decode, i32 0, i32 0)) #5, !dbg !272
  unreachable, !dbg !272
                                                  ; No predecessors!
  br label %cond.end, !dbg !274

cond.end:                                         ; preds = %41, %cond.true
  %42 = load i64*, i64** %in_pos.addr, align 8, !dbg !276
  %43 = load i64, i64* %42, align 8, !dbg !278
  %44 = load i64, i64* %in_size.addr, align 8, !dbg !279
  %cmp23 = icmp eq i64 %43, %44, !dbg !280
  br i1 %cmp23, label %if.then24, label %if.else25, !dbg !281

if.then24:                                        ; preds = %cond.end
  store i32 9, i32* %ret, align 4, !dbg !282
  br label %if.end26, !dbg !283

if.else25:                                        ; preds = %cond.end
  store i32 10, i32* %ret, align 4, !dbg !284
  br label %if.end26

if.end26:                                         ; preds = %if.else25, %if.then24
  br label %if.end27, !dbg !285

if.end27:                                         ; preds = %if.end26, %if.else
  %45 = load i64, i64* %in_start, align 8, !dbg !286
  %46 = load i64*, i64** %in_pos.addr, align 8, !dbg !287
  store i64 %45, i64* %46, align 8, !dbg !288
  %47 = load i64, i64* %out_start, align 8, !dbg !289
  %48 = load i64*, i64** %out_pos.addr, align 8, !dbg !290
  store i64 %47, i64* %48, align 8, !dbg !291
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.then17
  br label %if.end29, !dbg !292

if.end29:                                         ; preds = %if.end28, %if.end
  %49 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !293
  call void @lzma_next_end(%struct.lzma_next_coder_s* %block_decoder, %struct.lzma_allocator* %49), !dbg !294
  %50 = load i32, i32* %ret, align 4, !dbg !295
  store i32 %50, i32* %retval, align 4, !dbg !296
  br label %return, !dbg !296

return:                                           ; preds = %if.end29, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !297
  ret i32 %51, !dbg !297
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!163, !164}
!llvm.ident = !{!165}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !34, subprograms: !36, globals: !118)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25, !28}
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
!28 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !29)
!29 = !{!30, !31, !32, !33}
!30 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!31 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!32 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!33 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!34 = !{!35}
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!36 = !{!37}
!37 = distinct !DISubprogram(name: "lzma_block_buffer_decode", scope: !1, file: !1, line: 17, type: !38, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!38 = !DISubroutineType(types: !39)
!39 = !{!40, !41, !98, !113, !115, !106, !116, !115, !106}
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !43, line: 245, baseType: !44)
!43 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!44 = !DICompositeType(tag: DW_TAG_structure_type, file: !43, line: 30, size: 1664, align: 64, elements: !45)
!45 = !{!46, !50, !51, !53, !58, !59, !67, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !86, !87, !88, !89, !91, !92, !93, !94, !95, !96, !97}
!46 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !44, file: !43, line: 47, baseType: !47, size: 32, align: 32)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !48, line: 51, baseType: !49)
!48 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!49 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !44, file: !43, line: 67, baseType: !47, size: 32, align: 32, offset: 32)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !44, file: !43, line: 88, baseType: !52, size: 32, align: 32, offset: 64)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !44, file: !43, line: 143, baseType: !54, size: 64, align: 64, offset: 128)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !55, line: 63, baseType: !56)
!55 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !48, line: 55, baseType: !57)
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !44, file: !43, line: 167, baseType: !54, size: 64, align: 64, offset: 192)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !44, file: !43, line: 195, baseType: !60, size: 64, align: 64, offset: 256)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !62, line: 65, baseType: !63)
!62 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!63 = !DICompositeType(tag: DW_TAG_structure_type, file: !62, line: 43, size: 128, align: 64, elements: !64)
!64 = !{!65, !66}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !63, file: !62, line: 54, baseType: !54, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !63, file: !62, line: 63, baseType: !35, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !44, file: !43, line: 212, baseType: !68, size: 512, align: 8, offset: 320)
!68 = !DICompositeType(tag: DW_TAG_array_type, baseType: !69, size: 512, align: 8, elements: !71)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !48, line: 48, baseType: !70)
!70 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!71 = !{!72}
!72 = !DISubrange(count: 64)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !44, file: !43, line: 221, baseType: !35, size: 64, align: 64, offset: 832)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !44, file: !43, line: 222, baseType: !35, size: 64, align: 64, offset: 896)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !44, file: !43, line: 223, baseType: !35, size: 64, align: 64, offset: 960)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !44, file: !43, line: 224, baseType: !47, size: 32, align: 32, offset: 1024)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !44, file: !43, line: 225, baseType: !47, size: 32, align: 32, offset: 1056)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !44, file: !43, line: 226, baseType: !54, size: 64, align: 64, offset: 1088)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !44, file: !43, line: 227, baseType: !54, size: 64, align: 64, offset: 1152)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !44, file: !43, line: 228, baseType: !54, size: 64, align: 64, offset: 1216)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !44, file: !43, line: 229, baseType: !54, size: 64, align: 64, offset: 1280)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !44, file: !43, line: 230, baseType: !54, size: 64, align: 64, offset: 1344)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !44, file: !43, line: 231, baseType: !54, size: 64, align: 64, offset: 1408)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !44, file: !43, line: 232, baseType: !85, size: 32, align: 32, offset: 1472)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !44, file: !43, line: 233, baseType: !85, size: 32, align: 32, offset: 1504)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !44, file: !43, line: 234, baseType: !85, size: 32, align: 32, offset: 1536)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !44, file: !43, line: 235, baseType: !85, size: 32, align: 32, offset: 1568)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !44, file: !43, line: 236, baseType: !90, size: 8, align: 8, offset: 1600)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !70)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !44, file: !43, line: 237, baseType: !90, size: 8, align: 8, offset: 1608)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !44, file: !43, line: 238, baseType: !90, size: 8, align: 8, offset: 1616)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !44, file: !43, line: 239, baseType: !90, size: 8, align: 8, offset: 1624)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !44, file: !43, line: 240, baseType: !90, size: 8, align: 8, offset: 1632)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !44, file: !43, line: 241, baseType: !90, size: 8, align: 8, offset: 1640)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !44, file: !43, line: 242, baseType: !90, size: 8, align: 8, offset: 1648)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !44, file: !43, line: 243, baseType: !90, size: 8, align: 8, offset: 1656)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !100)
!100 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !101)
!101 = !{!102, !108, !112}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !100, file: !4, line: 376, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DISubroutineType(types: !105)
!105 = !{!35, !35, !106, !106}
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !107, line: 62, baseType: !57)
!107 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!108 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !100, file: !4, line: 390, baseType: !109, size: 64, align: 64, offset: 64)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DISubroutineType(types: !111)
!111 = !{null, !35, !35}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !100, file: !4, line: 401, baseType: !35, size: 64, align: 64, offset: 128)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !69)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!117 = !{}
!118 = !{!119}
!119 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !120, line: 159, type: !121, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!120 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !122)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !120, line: 75, baseType: !123)
!123 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !120, line: 119, size: 512, align: 64, elements: !124)
!124 = !{!125, !129, !130, !132, !141, !146, !152, !157}
!125 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !123, file: !120, line: 121, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !120, line: 73, baseType: !128)
!128 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !120, line: 73, flags: DIFlagFwdDecl)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !123, file: !120, line: 125, baseType: !54, size: 64, align: 64, offset: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !123, file: !120, line: 131, baseType: !131, size: 64, align: 64, offset: 128)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !48, line: 122, baseType: !57)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !123, file: !120, line: 134, baseType: !133, size: 64, align: 64, offset: 192)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !120, line: 89, baseType: !134)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DISubroutineType(types: !136)
!136 = !{!40, !126, !98, !137, !138, !106, !139, !138, !106, !140}
!137 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !113)
!138 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !115)
!139 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !116)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !28)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !123, file: !120, line: 139, baseType: !142, size: 64, align: 64, offset: 256)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !120, line: 97, baseType: !143)
!143 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !144, size: 64, align: 64)
!144 = !DISubroutineType(types: !145)
!145 = !{null, !126, !98}
!146 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !123, file: !120, line: 143, baseType: !147, size: 64, align: 64, offset: 320)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DISubroutineType(types: !149)
!149 = !{!52, !150}
!150 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !151, size: 64, align: 64)
!151 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !127)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !123, file: !120, line: 147, baseType: !153, size: 64, align: 64, offset: 384)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DISubroutineType(types: !155)
!155 = !{!40, !126, !156, !156, !56}
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !123, file: !120, line: 152, baseType: !158, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DISubroutineType(types: !160)
!160 = !{!40, !126, !98, !161, !161}
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !61)
!163 = !{i32 2, !"Dwarf Version", i32 4}
!164 = !{i32 2, !"Debug Info Version", i32 3}
!165 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!166 = !DILocalVariable(name: "block", arg: 1, scope: !37, file: !1, line: 17, type: !41)
!167 = !DIExpression()
!168 = !DILocation(line: 17, column: 38, scope: !37)
!169 = !DILocalVariable(name: "allocator", arg: 2, scope: !37, file: !1, line: 17, type: !98)
!170 = !DILocation(line: 17, column: 61, scope: !37)
!171 = !DILocalVariable(name: "in", arg: 3, scope: !37, file: !1, line: 18, type: !113)
!172 = !DILocation(line: 18, column: 18, scope: !37)
!173 = !DILocalVariable(name: "in_pos", arg: 4, scope: !37, file: !1, line: 18, type: !115)
!174 = !DILocation(line: 18, column: 30, scope: !37)
!175 = !DILocalVariable(name: "in_size", arg: 5, scope: !37, file: !1, line: 18, type: !106)
!176 = !DILocation(line: 18, column: 45, scope: !37)
!177 = !DILocalVariable(name: "out", arg: 6, scope: !37, file: !1, line: 19, type: !116)
!178 = !DILocation(line: 19, column: 12, scope: !37)
!179 = !DILocalVariable(name: "out_pos", arg: 7, scope: !37, file: !1, line: 19, type: !115)
!180 = !DILocation(line: 19, column: 25, scope: !37)
!181 = !DILocalVariable(name: "out_size", arg: 8, scope: !37, file: !1, line: 19, type: !106)
!182 = !DILocation(line: 19, column: 41, scope: !37)
!183 = !DILocalVariable(name: "block_decoder", scope: !37, file: !1, line: 21, type: !122)
!184 = !DILocation(line: 21, column: 18, scope: !37)
!185 = !DILocalVariable(name: "ret", scope: !37, file: !1, line: 22, type: !40)
!186 = !DILocation(line: 22, column: 11, scope: !37)
!187 = !DILocation(line: 24, column: 6, scope: !188)
!188 = distinct !DILexicalBlock(scope: !37, file: !1, line: 24, column: 6)
!189 = !DILocation(line: 24, column: 13, scope: !188)
!190 = !DILocation(line: 24, column: 21, scope: !188)
!191 = !DILocation(line: 24, column: 25, scope: !192)
!192 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 1)
!193 = !DILocation(line: 24, column: 28, scope: !192)
!194 = !DILocation(line: 24, column: 36, scope: !192)
!195 = !DILocation(line: 24, column: 40, scope: !196)
!196 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 2)
!197 = !DILocation(line: 24, column: 39, scope: !196)
!198 = !DILocation(line: 24, column: 50, scope: !196)
!199 = !DILocation(line: 24, column: 47, scope: !196)
!200 = !DILocation(line: 25, column: 4, scope: !188)
!201 = !DILocation(line: 25, column: 8, scope: !192)
!202 = !DILocation(line: 25, column: 7, scope: !192)
!203 = !DILocation(line: 25, column: 17, scope: !192)
!204 = !DILocation(line: 25, column: 15, scope: !192)
!205 = !DILocation(line: 25, column: 25, scope: !192)
!206 = !DILocation(line: 25, column: 28, scope: !196)
!207 = !DILocation(line: 25, column: 36, scope: !196)
!208 = !DILocation(line: 26, column: 4, scope: !188)
!209 = !DILocation(line: 26, column: 8, scope: !192)
!210 = !DILocation(line: 26, column: 12, scope: !192)
!211 = !DILocation(line: 26, column: 20, scope: !192)
!212 = !DILocation(line: 26, column: 24, scope: !196)
!213 = !DILocation(line: 26, column: 23, scope: !196)
!214 = !DILocation(line: 26, column: 35, scope: !196)
!215 = !DILocation(line: 26, column: 32, scope: !196)
!216 = !DILocation(line: 27, column: 4, scope: !188)
!217 = !DILocation(line: 27, column: 8, scope: !192)
!218 = !DILocation(line: 27, column: 7, scope: !192)
!219 = !DILocation(line: 27, column: 18, scope: !192)
!220 = !DILocation(line: 27, column: 16, scope: !192)
!221 = !DILocation(line: 24, column: 6, scope: !222)
!222 = !DILexicalBlockFile(scope: !37, file: !1, discriminator: 3)
!223 = !DILocation(line: 28, column: 3, scope: !188)
!224 = !DILocation(line: 31, column: 18, scope: !37)
!225 = !DILocation(line: 32, column: 48, scope: !37)
!226 = !DILocation(line: 32, column: 59, scope: !37)
!227 = !DILocation(line: 32, column: 8, scope: !37)
!228 = !DILocation(line: 32, column: 6, scope: !37)
!229 = !DILocation(line: 34, column: 6, scope: !230)
!230 = distinct !DILexicalBlock(scope: !37, file: !1, line: 34, column: 6)
!231 = !DILocation(line: 34, column: 10, scope: !230)
!232 = !DILocation(line: 34, column: 6, scope: !37)
!233 = !DILocalVariable(name: "in_start", scope: !234, file: !1, line: 37, type: !235)
!234 = distinct !DILexicalBlock(scope: !230, file: !1, line: 34, column: 22)
!235 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !106)
!236 = !DILocation(line: 37, column: 16, scope: !234)
!237 = !DILocation(line: 37, column: 28, scope: !234)
!238 = !DILocation(line: 37, column: 27, scope: !234)
!239 = !DILocalVariable(name: "out_start", scope: !234, file: !1, line: 38, type: !235)
!240 = !DILocation(line: 38, column: 16, scope: !234)
!241 = !DILocation(line: 38, column: 29, scope: !234)
!242 = !DILocation(line: 38, column: 28, scope: !234)
!243 = !DILocation(line: 41, column: 23, scope: !234)
!244 = !DILocation(line: 41, column: 42, scope: !234)
!245 = !DILocation(line: 41, column: 49, scope: !234)
!246 = !DILocation(line: 42, column: 5, scope: !234)
!247 = !DILocation(line: 42, column: 9, scope: !234)
!248 = !DILocation(line: 42, column: 17, scope: !234)
!249 = !DILocation(line: 42, column: 26, scope: !234)
!250 = !DILocation(line: 42, column: 31, scope: !234)
!251 = !DILocation(line: 42, column: 40, scope: !234)
!252 = !DILocation(line: 41, column: 9, scope: !234)
!253 = !DILocation(line: 41, column: 7, scope: !234)
!254 = !DILocation(line: 45, column: 7, scope: !255)
!255 = distinct !DILexicalBlock(scope: !234, file: !1, line: 45, column: 7)
!256 = !DILocation(line: 45, column: 11, scope: !255)
!257 = !DILocation(line: 45, column: 7, scope: !234)
!258 = !DILocation(line: 46, column: 8, scope: !259)
!259 = distinct !DILexicalBlock(scope: !255, file: !1, line: 45, column: 31)
!260 = !DILocation(line: 47, column: 3, scope: !259)
!261 = !DILocation(line: 48, column: 8, scope: !262)
!262 = distinct !DILexicalBlock(scope: !263, file: !1, line: 48, column: 8)
!263 = distinct !DILexicalBlock(scope: !255, file: !1, line: 47, column: 10)
!264 = !DILocation(line: 48, column: 12, scope: !262)
!265 = !DILocation(line: 48, column: 8, scope: !263)
!266 = !DILocation(line: 51, column: 5, scope: !267)
!267 = distinct !DILexicalBlock(scope: !262, file: !1, line: 48, column: 24)
!268 = !DILocation(line: 51, column: 5, scope: !269)
!269 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 1)
!270 = !DILocation(line: 51, column: 5, scope: !271)
!271 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 2)
!272 = !DILocation(line: 51, column: 5, scope: !273)
!273 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 3)
!274 = !DILocation(line: 51, column: 5, scope: !275)
!275 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 4)
!276 = !DILocation(line: 64, column: 10, scope: !277)
!277 = distinct !DILexicalBlock(scope: !267, file: !1, line: 64, column: 9)
!278 = !DILocation(line: 64, column: 9, scope: !277)
!279 = !DILocation(line: 64, column: 20, scope: !277)
!280 = !DILocation(line: 64, column: 17, scope: !277)
!281 = !DILocation(line: 64, column: 9, scope: !267)
!282 = !DILocation(line: 65, column: 10, scope: !277)
!283 = !DILocation(line: 65, column: 6, scope: !277)
!284 = !DILocation(line: 67, column: 10, scope: !277)
!285 = !DILocation(line: 68, column: 4, scope: !267)
!286 = !DILocation(line: 71, column: 14, scope: !263)
!287 = !DILocation(line: 71, column: 5, scope: !263)
!288 = !DILocation(line: 71, column: 12, scope: !263)
!289 = !DILocation(line: 72, column: 15, scope: !263)
!290 = !DILocation(line: 72, column: 5, scope: !263)
!291 = !DILocation(line: 72, column: 13, scope: !263)
!292 = !DILocation(line: 74, column: 2, scope: !234)
!293 = !DILocation(line: 79, column: 32, scope: !37)
!294 = !DILocation(line: 79, column: 2, scope: !37)
!295 = !DILocation(line: 81, column: 9, scope: !37)
!296 = !DILocation(line: 81, column: 2, scope: !37)
!297 = !DILocation(line: 82, column: 1, scope: !37)
