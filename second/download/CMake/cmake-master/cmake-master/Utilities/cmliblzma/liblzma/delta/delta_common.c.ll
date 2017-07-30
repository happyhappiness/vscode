; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_common.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i64, i8, [256 x i8] }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_options_delta = type { i32, i32, i32, i32, i32, i32, i8*, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8

; Function Attrs: nounwind uwtable
define i32 @lzma_delta_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !38 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %opt = alloca %struct.lzma_options_delta*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !150, metadata !151), !dbg !152
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !153, metadata !151), !dbg !154
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !155, metadata !151), !dbg !156
  call void @llvm.dbg.declare(metadata %struct.lzma_options_delta** %opt, metadata !157, metadata !151), !dbg !174
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !175
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 0, !dbg !177
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !177
  %cmp = icmp eq %struct.lzma_coder_s* %1, null, !dbg !178
  br i1 %cmp, label %if.then, label %if.end7, !dbg !179

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !180
  %call = call noalias i8* @lzma_alloc(i64 336, %struct.lzma_allocator* %2), !dbg !182
  %3 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !182
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !183
  %coder1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 0, !dbg !184
  store %struct.lzma_coder_s* %3, %struct.lzma_coder_s** %coder1, align 8, !dbg !185
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !186
  %coder2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %5, i32 0, i32 0, !dbg !188
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !188
  %cmp3 = icmp eq %struct.lzma_coder_s* %6, null, !dbg !189
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !190

if.then4:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !191
  br label %return, !dbg !191

if.end:                                           ; preds = %if.then
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !192
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 4, !dbg !193
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @delta_coder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !194
  %8 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !195
  %coder5 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %8, i32 0, i32 0, !dbg !196
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !196
  %next6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 0, !dbg !197
  %10 = bitcast %struct.lzma_next_coder_s* %next6 to i8*, !dbg !198
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !198
  br label %if.end7, !dbg !199

if.end7:                                          ; preds = %if.end, %entry
  %11 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !200
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %11, i64 0, !dbg !200
  %options = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 2, !dbg !202
  %12 = load i8*, i8** %options, align 8, !dbg !202
  %call8 = call i64 @lzma_delta_coder_memusage(i8* %12), !dbg !203
  %cmp9 = icmp eq i64 %call8, -1, !dbg !204
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !205

if.then10:                                        ; preds = %if.end7
  store i32 8, i32* %retval, align 4, !dbg !206
  br label %return, !dbg !206

if.end11:                                         ; preds = %if.end7
  %13 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !207
  %arrayidx12 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %13, i64 0, !dbg !207
  %options13 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx12, i32 0, i32 2, !dbg !208
  %14 = load i8*, i8** %options13, align 8, !dbg !208
  %15 = bitcast i8* %14 to %struct.lzma_options_delta*, !dbg !207
  store %struct.lzma_options_delta* %15, %struct.lzma_options_delta** %opt, align 8, !dbg !209
  %16 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !210
  %dist = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %16, i32 0, i32 1, !dbg !211
  %17 = load i32, i32* %dist, align 4, !dbg !211
  %conv = zext i32 %17 to i64, !dbg !210
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !212
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 0, !dbg !213
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !213
  %distance = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 1, !dbg !214
  store i64 %conv, i64* %distance, align 8, !dbg !215
  %20 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !216
  %coder15 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %20, i32 0, i32 0, !dbg !217
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder15, align 8, !dbg !217
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 2, !dbg !218
  store i8 0, i8* %pos, align 8, !dbg !219
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !220
  %coder16 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !220
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder16, align 8, !dbg !220
  %history = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 3, !dbg !220
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %history, i32 0, i32 0, !dbg !220
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 256, i32 1, i1 false), !dbg !220
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !221
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !222
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !222
  %next18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 0, !dbg !223
  %26 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !224
  %27 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !225
  %add.ptr = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %27, i64 1, !dbg !226
  %call19 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next18, %struct.lzma_allocator* %26, %struct.lzma_filter_info_s* %add.ptr), !dbg !227
  store i32 %call19, i32* %retval, align 4, !dbg !228
  br label %return, !dbg !228

return:                                           ; preds = %if.end11, %if.then10, %if.then4
  %28 = load i32, i32* %retval, align 4, !dbg !229
  ret i32 %28, !dbg !229
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal void @delta_coder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !143 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !230, metadata !151), !dbg !231
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !232, metadata !151), !dbg !233
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !234
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !235
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !236
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !237
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !238
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !238
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !239
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !240
  ret void, !dbg !241
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i64 @lzma_delta_coder_memusage(i8* %options) #0 !dbg !138 {
entry:
  %retval = alloca i64, align 8
  %options.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_delta*, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !242, metadata !151), !dbg !243
  call void @llvm.dbg.declare(metadata %struct.lzma_options_delta** %opt, metadata !244, metadata !151), !dbg !245
  %0 = load i8*, i8** %options.addr, align 8, !dbg !246
  %1 = bitcast i8* %0 to %struct.lzma_options_delta*, !dbg !246
  store %struct.lzma_options_delta* %1, %struct.lzma_options_delta** %opt, align 8, !dbg !245
  %2 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !247
  %cmp = icmp eq %struct.lzma_options_delta* %2, null, !dbg !249
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !250

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !251
  %type = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %3, i32 0, i32 0, !dbg !253
  %4 = load i32, i32* %type, align 8, !dbg !253
  %cmp1 = icmp ne i32 %4, 0, !dbg !254
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !255

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %5 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !256
  %dist = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %5, i32 0, i32 1, !dbg !257
  %6 = load i32, i32* %dist, align 4, !dbg !257
  %cmp3 = icmp ult i32 %6, 1, !dbg !258
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !259

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %7 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !260
  %dist5 = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %7, i32 0, i32 1, !dbg !261
  %8 = load i32, i32* %dist5, align 4, !dbg !261
  %cmp6 = icmp ugt i32 %8, 256, !dbg !262
  br i1 %cmp6, label %if.then, label %if.end, !dbg !263

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i64 -1, i64* %retval, align 8, !dbg !265
  br label %return, !dbg !265

if.end:                                           ; preds = %lor.lhs.false4
  store i64 336, i64* %retval, align 8, !dbg !266
  br label %return, !dbg !266

return:                                           ; preds = %if.end, %if.then
  %9 = load i64, i64* %retval, align 8, !dbg !267
  ret i64 %9, !dbg !267
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!147, !148}
!llvm.ident = !{!149}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !35, subprograms: !37, globals: !144)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_common.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24, !31}
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
!31 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !32, line: 35, size: 32, align: 32, elements: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/delta.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !{!34}
!34 = !DIEnumerator(name: "LZMA_DELTA_TYPE_BYTE", value: 0)
!35 = !{!36}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!37 = !{!38, !138, !143}
!38 = distinct !DISubprogram(name: "lzma_delta_coder_init", scope: !1, file: !1, line: 27, type: !39, isLocal: false, isDefinition: true, scopeLine: 29, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!39 = !DISubroutineType(types: !40)
!40 = !{!41, !42, !77, !127}
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !44, line: 75, baseType: !45)
!44 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !44, line: 119, size: 512, align: 64, elements: !46)
!46 = !{!47, !66, !70, !72, !98, !103, !110, !115}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !45, file: !44, line: 121, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !44, line: 73, baseType: !50)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !51, line: 18, size: 2688, align: 64, elements: !52)
!51 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!52 = !{!53, !54, !58, !62}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !50, file: !51, line: 20, baseType: !43, size: 512, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "distance", scope: !50, file: !51, line: 23, baseType: !55, size: 64, align: 64, offset: 512)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !57)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !50, file: !51, line: 26, baseType: !59, size: 8, align: 8, offset: 576)
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !60, line: 48, baseType: !61)
!60 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "history", scope: !50, file: !51, line: 29, baseType: !63, size: 2048, align: 8, offset: 584)
!63 = !DICompositeType(tag: DW_TAG_array_type, baseType: !59, size: 2048, align: 8, elements: !64)
!64 = !{!65}
!65 = !DISubrange(count: 256)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !45, file: !44, line: 125, baseType: !67, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !68, line: 63, baseType: !69)
!68 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !60, line: 55, baseType: !57)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !45, file: !44, line: 131, baseType: !71, size: 64, align: 64, offset: 128)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !60, line: 122, baseType: !57)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !45, file: !44, line: 134, baseType: !73, size: 64, align: 64, offset: 192)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !44, line: 89, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!41, !48, !77, !90, !93, !55, !95, !93, !55, !97}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !80)
!80 = !{!81, !85, !89}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !79, file: !4, line: 376, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!36, !36, !55, !55}
!85 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !79, file: !4, line: 390, baseType: !86, size: 64, align: 64, offset: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !36, !36}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !79, file: !4, line: 401, baseType: !36, size: 64, align: 64, offset: 128)
!90 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !91)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !59)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !94)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !96)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !45, file: !44, line: 139, baseType: !99, size: 64, align: 64, offset: 256)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !44, line: 97, baseType: !100)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{null, !48, !77}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !45, file: !44, line: 143, baseType: !104, size: 64, align: 64, offset: 320)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !108}
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !45, file: !44, line: 147, baseType: !111, size: 64, align: 64, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DISubroutineType(types: !113)
!113 = !{!41, !48, !114, !114, !69}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !45, file: !44, line: 152, baseType: !116, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!41, !48, !77, !119, !119}
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !121)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !122, line: 65, baseType: !123)
!122 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!123 = !DICompositeType(tag: DW_TAG_structure_type, file: !122, line: 43, size: 128, align: 64, elements: !124)
!124 = !{!125, !126}
!125 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !123, file: !122, line: 54, baseType: !67, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !123, file: !122, line: 63, baseType: !36, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !44, line: 77, baseType: !130)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !44, line: 104, size: 192, align: 64, elements: !131)
!131 = !{!132, !133, !136}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !130, file: !44, line: 107, baseType: !67, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !130, file: !44, line: 111, baseType: !134, size: 64, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !44, line: 81, baseType: !135)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !130, file: !44, line: 114, baseType: !36, size: 64, align: 64, offset: 128)
!137 = !{}
!138 = distinct !DISubprogram(name: "lzma_delta_coder_memusage", scope: !1, file: !1, line: 62, type: !139, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!139 = !DISubroutineType(types: !140)
!140 = !{!69, !141}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!143 = distinct !DISubprogram(name: "delta_coder_end", scope: !1, file: !1, line: 18, type: !101, isLocal: true, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!144 = !{!145}
!145 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !44, line: 159, type: !146, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!146 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !43)
!147 = !{i32 2, !"Dwarf Version", i32 4}
!148 = !{i32 2, !"Debug Info Version", i32 3}
!149 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!150 = !DILocalVariable(name: "next", arg: 1, scope: !38, file: !1, line: 27, type: !42)
!151 = !DIExpression()
!152 = !DILocation(line: 27, column: 40, scope: !38)
!153 = !DILocalVariable(name: "allocator", arg: 2, scope: !38, file: !1, line: 27, type: !77)
!154 = !DILocation(line: 27, column: 62, scope: !38)
!155 = !DILocalVariable(name: "filters", arg: 3, scope: !38, file: !1, line: 28, type: !127)
!156 = !DILocation(line: 28, column: 27, scope: !38)
!157 = !DILocalVariable(name: "opt", scope: !38, file: !1, line: 30, type: !158)
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !160)
!160 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_delta", file: !32, line: 77, baseType: !161)
!161 = !DICompositeType(tag: DW_TAG_structure_type, file: !32, line: 45, size: 320, align: 64, elements: !162)
!162 = !{!163, !165, !168, !169, !170, !171, !172, !173}
!163 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !161, file: !32, line: 47, baseType: !164, size: 32, align: 32)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_delta_type", file: !32, line: 37, baseType: !31)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !161, file: !32, line: 59, baseType: !166, size: 32, align: 32, offset: 32)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !60, line: 51, baseType: !167)
!167 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !161, file: !32, line: 70, baseType: !166, size: 32, align: 32, offset: 64)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !161, file: !32, line: 71, baseType: !166, size: 32, align: 32, offset: 96)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !161, file: !32, line: 72, baseType: !166, size: 32, align: 32, offset: 128)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !161, file: !32, line: 73, baseType: !166, size: 32, align: 32, offset: 160)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !161, file: !32, line: 74, baseType: !36, size: 64, align: 64, offset: 192)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !161, file: !32, line: 75, baseType: !36, size: 64, align: 64, offset: 256)
!174 = !DILocation(line: 30, column: 28, scope: !38)
!175 = !DILocation(line: 33, column: 6, scope: !176)
!176 = distinct !DILexicalBlock(scope: !38, file: !1, line: 33, column: 6)
!177 = !DILocation(line: 33, column: 12, scope: !176)
!178 = !DILocation(line: 33, column: 18, scope: !176)
!179 = !DILocation(line: 33, column: 6, scope: !38)
!180 = !DILocation(line: 34, column: 48, scope: !181)
!181 = distinct !DILexicalBlock(scope: !176, file: !1, line: 33, column: 27)
!182 = !DILocation(line: 34, column: 17, scope: !181)
!183 = !DILocation(line: 34, column: 3, scope: !181)
!184 = !DILocation(line: 34, column: 9, scope: !181)
!185 = !DILocation(line: 34, column: 15, scope: !181)
!186 = !DILocation(line: 35, column: 7, scope: !187)
!187 = distinct !DILexicalBlock(scope: !181, file: !1, line: 35, column: 7)
!188 = !DILocation(line: 35, column: 13, scope: !187)
!189 = !DILocation(line: 35, column: 19, scope: !187)
!190 = !DILocation(line: 35, column: 7, scope: !181)
!191 = !DILocation(line: 36, column: 4, scope: !187)
!192 = !DILocation(line: 39, column: 3, scope: !181)
!193 = !DILocation(line: 39, column: 9, scope: !181)
!194 = !DILocation(line: 39, column: 13, scope: !181)
!195 = !DILocation(line: 40, column: 3, scope: !181)
!196 = !DILocation(line: 40, column: 9, scope: !181)
!197 = !DILocation(line: 40, column: 16, scope: !181)
!198 = !DILocation(line: 40, column: 23, scope: !181)
!199 = !DILocation(line: 41, column: 2, scope: !181)
!200 = !DILocation(line: 44, column: 32, scope: !201)
!201 = distinct !DILexicalBlock(scope: !38, file: !1, line: 44, column: 6)
!202 = !DILocation(line: 44, column: 43, scope: !201)
!203 = !DILocation(line: 44, column: 6, scope: !201)
!204 = !DILocation(line: 44, column: 52, scope: !201)
!205 = !DILocation(line: 44, column: 6, scope: !38)
!206 = !DILocation(line: 45, column: 3, scope: !201)
!207 = !DILocation(line: 48, column: 8, scope: !38)
!208 = !DILocation(line: 48, column: 19, scope: !38)
!209 = !DILocation(line: 48, column: 6, scope: !38)
!210 = !DILocation(line: 49, column: 26, scope: !38)
!211 = !DILocation(line: 49, column: 31, scope: !38)
!212 = !DILocation(line: 49, column: 2, scope: !38)
!213 = !DILocation(line: 49, column: 8, scope: !38)
!214 = !DILocation(line: 49, column: 15, scope: !38)
!215 = !DILocation(line: 49, column: 24, scope: !38)
!216 = !DILocation(line: 52, column: 2, scope: !38)
!217 = !DILocation(line: 52, column: 8, scope: !38)
!218 = !DILocation(line: 52, column: 15, scope: !38)
!219 = !DILocation(line: 52, column: 19, scope: !38)
!220 = !DILocation(line: 53, column: 2, scope: !38)
!221 = !DILocation(line: 56, column: 32, scope: !38)
!222 = !DILocation(line: 56, column: 38, scope: !38)
!223 = !DILocation(line: 56, column: 45, scope: !38)
!224 = !DILocation(line: 57, column: 4, scope: !38)
!225 = !DILocation(line: 57, column: 15, scope: !38)
!226 = !DILocation(line: 57, column: 23, scope: !38)
!227 = !DILocation(line: 56, column: 9, scope: !38)
!228 = !DILocation(line: 56, column: 2, scope: !38)
!229 = !DILocation(line: 58, column: 1, scope: !38)
!230 = !DILocalVariable(name: "coder", arg: 1, scope: !143, file: !1, line: 18, type: !48)
!231 = !DILocation(line: 18, column: 29, scope: !143)
!232 = !DILocalVariable(name: "allocator", arg: 2, scope: !143, file: !1, line: 18, type: !77)
!233 = !DILocation(line: 18, column: 52, scope: !143)
!234 = !DILocation(line: 20, column: 17, scope: !143)
!235 = !DILocation(line: 20, column: 24, scope: !143)
!236 = !DILocation(line: 20, column: 30, scope: !143)
!237 = !DILocation(line: 20, column: 2, scope: !143)
!238 = !DILocation(line: 21, column: 12, scope: !143)
!239 = !DILocation(line: 21, column: 19, scope: !143)
!240 = !DILocation(line: 21, column: 2, scope: !143)
!241 = !DILocation(line: 22, column: 2, scope: !143)
!242 = !DILocalVariable(name: "options", arg: 1, scope: !138, file: !1, line: 62, type: !141)
!243 = !DILocation(line: 62, column: 39, scope: !138)
!244 = !DILocalVariable(name: "opt", scope: !138, file: !1, line: 64, type: !158)
!245 = !DILocation(line: 64, column: 28, scope: !138)
!246 = !DILocation(line: 64, column: 34, scope: !138)
!247 = !DILocation(line: 66, column: 6, scope: !248)
!248 = distinct !DILexicalBlock(scope: !138, file: !1, line: 66, column: 6)
!249 = !DILocation(line: 66, column: 10, scope: !248)
!250 = !DILocation(line: 66, column: 18, scope: !248)
!251 = !DILocation(line: 66, column: 21, scope: !252)
!252 = !DILexicalBlockFile(scope: !248, file: !1, discriminator: 1)
!253 = !DILocation(line: 66, column: 26, scope: !252)
!254 = !DILocation(line: 66, column: 31, scope: !252)
!255 = !DILocation(line: 67, column: 4, scope: !248)
!256 = !DILocation(line: 67, column: 7, scope: !252)
!257 = !DILocation(line: 67, column: 12, scope: !252)
!258 = !DILocation(line: 67, column: 17, scope: !252)
!259 = !DILocation(line: 68, column: 4, scope: !248)
!260 = !DILocation(line: 68, column: 7, scope: !252)
!261 = !DILocation(line: 68, column: 12, scope: !252)
!262 = !DILocation(line: 68, column: 17, scope: !252)
!263 = !DILocation(line: 66, column: 6, scope: !264)
!264 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 2)
!265 = !DILocation(line: 69, column: 3, scope: !248)
!266 = !DILocation(line: 71, column: 2, scope: !138)
!267 = !DILocation(line: 72, column: 1, scope: !138)
