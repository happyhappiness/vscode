; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [43 x i8] c"*in_pos == in_size || *out_pos == out_size\00", align 1
@.str.1 = private unnamed_addr constant [93 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_decoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_raw_buffer_decode = private unnamed_addr constant [135 x i8] c"lzma_ret lzma_raw_buffer_decode(const lzma_filter *, lzma_allocator *, const uint8_t *, size_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_buffer_decode(%struct.lzma_filter* %filters, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %next = alloca %struct.lzma_next_coder_s, align 8
  %in_start = alloca i64, align 8
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %tmp = alloca [1 x i8], align 1
  %tmp_pos = alloca i64, align 8
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !120, metadata !121), !dbg !122
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !123, metadata !121), !dbg !124
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !125, metadata !121), !dbg !126
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !127, metadata !121), !dbg !128
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !129, metadata !121), !dbg !130
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !131, metadata !121), !dbg !132
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !133, metadata !121), !dbg !134
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !135, metadata !121), !dbg !136
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s* %next, metadata !137, metadata !121), !dbg !138
  %0 = bitcast %struct.lzma_next_coder_s* %next to i8*, !dbg !139
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !139
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !140, metadata !121), !dbg !141
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !142, metadata !121), !dbg !143
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !144, metadata !121), !dbg !145
  %1 = load i8*, i8** %in.addr, align 8, !dbg !146
  %cmp = icmp eq i8* %1, null, !dbg !148
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !149

lor.lhs.false:                                    ; preds = %entry
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !150
  %cmp1 = icmp eq i64* %2, null, !dbg !152
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !153

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !154
  %4 = load i64, i64* %3, align 8, !dbg !156
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !157
  %cmp3 = icmp ugt i64 %4, %5, !dbg !158
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !159

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %6 = load i8*, i8** %out.addr, align 8, !dbg !160
  %cmp5 = icmp eq i8* %6, null, !dbg !162
  br i1 %cmp5, label %if.then, label %lor.lhs.false6, !dbg !163

lor.lhs.false6:                                   ; preds = %lor.lhs.false4
  %7 = load i64*, i64** %out_pos.addr, align 8, !dbg !164
  %cmp7 = icmp eq i64* %7, null, !dbg !165
  br i1 %cmp7, label %if.then, label %lor.lhs.false8, !dbg !166

lor.lhs.false8:                                   ; preds = %lor.lhs.false6
  %8 = load i64*, i64** %out_pos.addr, align 8, !dbg !167
  %9 = load i64, i64* %8, align 8, !dbg !168
  %10 = load i64, i64* %out_size.addr, align 8, !dbg !169
  %cmp9 = icmp ugt i64 %9, %10, !dbg !170
  br i1 %cmp9, label %if.then, label %if.end, !dbg !171

if.then:                                          ; preds = %lor.lhs.false8, %lor.lhs.false6, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !173
  br label %return, !dbg !173

if.end:                                           ; preds = %lor.lhs.false8
  br label %do.body, !dbg !174

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !175, metadata !121), !dbg !178
  %11 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !179
  %12 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !179
  %call = call i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %11, %struct.lzma_filter* %12), !dbg !179
  store i32 %call, i32* %ret_, align 4, !dbg !179
  %13 = load i32, i32* %ret_, align 4, !dbg !179
  %cmp10 = icmp ne i32 %13, 0, !dbg !179
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !179

if.then11:                                        ; preds = %do.body
  %14 = load i32, i32* %ret_, align 4, !dbg !181
  store i32 %14, i32* %retval, align 4, !dbg !181
  br label %return, !dbg !181

if.end12:                                         ; preds = %do.body
  br label %do.end, !dbg !184

do.end:                                           ; preds = %if.end12
  %15 = load i64*, i64** %in_pos.addr, align 8, !dbg !186
  %16 = load i64, i64* %15, align 8, !dbg !187
  store i64 %16, i64* %in_start, align 8, !dbg !188
  %17 = load i64*, i64** %out_pos.addr, align 8, !dbg !189
  %18 = load i64, i64* %17, align 8, !dbg !190
  store i64 %18, i64* %out_start, align 8, !dbg !191
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !192
  %19 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !192
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 0, !dbg !193
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !193
  %21 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !194
  %22 = load i8*, i8** %in.addr, align 8, !dbg !195
  %23 = load i64*, i64** %in_pos.addr, align 8, !dbg !196
  %24 = load i64, i64* %in_size.addr, align 8, !dbg !197
  %25 = load i8*, i8** %out.addr, align 8, !dbg !198
  %26 = load i64*, i64** %out_pos.addr, align 8, !dbg !199
  %27 = load i64, i64* %out_size.addr, align 8, !dbg !200
  %call13 = call i32 %19(%struct.lzma_coder_s* %20, %struct.lzma_allocator* %21, i8* %22, i64* %23, i64 %24, i8* %25, i64* %26, i64 %27, i32 3), !dbg !201
  store i32 %call13, i32* %ret, align 4, !dbg !202
  %28 = load i32, i32* %ret, align 4, !dbg !203
  %cmp14 = icmp eq i32 %28, 1, !dbg !205
  br i1 %cmp14, label %if.then15, label %if.else, !dbg !206

if.then15:                                        ; preds = %do.end
  store i32 0, i32* %ret, align 4, !dbg !207
  br label %if.end38, !dbg !209

if.else:                                          ; preds = %do.end
  %29 = load i32, i32* %ret, align 4, !dbg !210
  %cmp16 = icmp eq i32 %29, 0, !dbg !213
  br i1 %cmp16, label %if.then17, label %if.end37, !dbg !214

if.then17:                                        ; preds = %if.else
  %30 = load i64*, i64** %in_pos.addr, align 8, !dbg !215
  %31 = load i64, i64* %30, align 8, !dbg !215
  %32 = load i64, i64* %in_size.addr, align 8, !dbg !215
  %cmp18 = icmp eq i64 %31, %32, !dbg !215
  br i1 %cmp18, label %cond.true, label %lor.lhs.false19, !dbg !215

lor.lhs.false19:                                  ; preds = %if.then17
  %33 = load i64*, i64** %out_pos.addr, align 8, !dbg !217
  %34 = load i64, i64* %33, align 8, !dbg !217
  %35 = load i64, i64* %out_size.addr, align 8, !dbg !217
  %cmp20 = icmp eq i64 %34, %35, !dbg !217
  br i1 %cmp20, label %cond.true, label %cond.false, !dbg !217

cond.true:                                        ; preds = %lor.lhs.false19, %if.then17
  br label %cond.end, !dbg !219

cond.false:                                       ; preds = %lor.lhs.false19
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([93 x i8], [93 x i8]* @.str.1, i32 0, i32 0), i32 49, i8* getelementptr inbounds ([135 x i8], [135 x i8]* @__PRETTY_FUNCTION__.lzma_raw_buffer_decode, i32 0, i32 0)) #5, !dbg !221
  unreachable, !dbg !221
                                                  ; No predecessors!
  br label %cond.end, !dbg !223

cond.end:                                         ; preds = %36, %cond.true
  %37 = load i64*, i64** %in_pos.addr, align 8, !dbg !225
  %38 = load i64, i64* %37, align 8, !dbg !227
  %39 = load i64, i64* %in_size.addr, align 8, !dbg !228
  %cmp21 = icmp ne i64 %38, %39, !dbg !229
  br i1 %cmp21, label %if.then22, label %if.else23, !dbg !230

if.then22:                                        ; preds = %cond.end
  store i32 10, i32* %ret, align 4, !dbg !231
  br label %if.end36, !dbg !233

if.else23:                                        ; preds = %cond.end
  %40 = load i64*, i64** %out_pos.addr, align 8, !dbg !234
  %41 = load i64, i64* %40, align 8, !dbg !237
  %42 = load i64, i64* %out_size.addr, align 8, !dbg !238
  %cmp24 = icmp ne i64 %41, %42, !dbg !239
  br i1 %cmp24, label %if.then25, label %if.else26, !dbg !237

if.then25:                                        ; preds = %if.else23
  store i32 9, i32* %ret, align 4, !dbg !240
  br label %if.end35, !dbg !242

if.else26:                                        ; preds = %if.else23
  call void @llvm.dbg.declare(metadata [1 x i8]* %tmp, metadata !243, metadata !121), !dbg !248
  call void @llvm.dbg.declare(metadata i64* %tmp_pos, metadata !249, metadata !121), !dbg !250
  store i64 0, i64* %tmp_pos, align 8, !dbg !250
  %code28 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !251
  %43 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code28, align 8, !dbg !251
  %coder29 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 0, !dbg !252
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder29, align 8, !dbg !252
  %45 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !253
  %46 = load i8*, i8** %in.addr, align 8, !dbg !254
  %47 = load i64*, i64** %in_pos.addr, align 8, !dbg !255
  %48 = load i64, i64* %in_size.addr, align 8, !dbg !256
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %tmp, i32 0, i32 0, !dbg !257
  %call30 = call i32 %43(%struct.lzma_coder_s* %44, %struct.lzma_allocator* %45, i8* %46, i64* %47, i64 %48, i8* %arraydecay, i64* %tmp_pos, i64 1, i32 3), !dbg !258
  %49 = load i64, i64* %tmp_pos, align 8, !dbg !259
  %cmp31 = icmp eq i64 %49, 1, !dbg !261
  br i1 %cmp31, label %if.then32, label %if.else33, !dbg !262

if.then32:                                        ; preds = %if.else26
  store i32 10, i32* %ret, align 4, !dbg !263
  br label %if.end34, !dbg !264

if.else33:                                        ; preds = %if.else26
  store i32 9, i32* %ret, align 4, !dbg !265
  br label %if.end34

if.end34:                                         ; preds = %if.else33, %if.then32
  br label %if.end35

if.end35:                                         ; preds = %if.end34, %if.then25
  br label %if.end36

if.end36:                                         ; preds = %if.end35, %if.then22
  br label %if.end37, !dbg !266

if.end37:                                         ; preds = %if.end36, %if.else
  %50 = load i64, i64* %in_start, align 8, !dbg !267
  %51 = load i64*, i64** %in_pos.addr, align 8, !dbg !268
  store i64 %50, i64* %51, align 8, !dbg !269
  %52 = load i64, i64* %out_start, align 8, !dbg !270
  %53 = load i64*, i64** %out_pos.addr, align 8, !dbg !271
  store i64 %52, i64* %53, align 8, !dbg !272
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.then15
  %54 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !273
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %54), !dbg !274
  %55 = load i32, i32* %ret, align 4, !dbg !275
  store i32 %55, i32* %retval, align 4, !dbg !276
  br label %return, !dbg !276

return:                                           ; preds = %if.end38, %if.then11, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !277
  ret i32 %56, !dbg !277
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #3

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
!llvm.module.flags = !{!117, !118}
!llvm.ident = !{!119}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !33, globals: !73)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!33 = !{!34}
!34 = distinct !DISubprogram(name: "lzma_raw_buffer_decode", scope: !1, file: !1, line: 17, type: !35, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !51, !66, !70, !59, !71, !70, !59}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !40)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !41, line: 65, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 43, size: 128, align: 64, elements: !43)
!43 = !{!44, !50}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !42, file: !41, line: 54, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !46, line: 63, baseType: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !48, line: 55, baseType: !49)
!48 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!49 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !42, file: !41, line: 63, baseType: !32, size: 64, align: 64, offset: 64)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !53)
!53 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !54)
!54 = !{!55, !61, !65}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !53, file: !4, line: 376, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{!32, !32, !59, !59}
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !60, line: 62, baseType: !49)
!60 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !53, file: !4, line: 390, baseType: !62, size: 64, align: 64, offset: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{null, !32, !32}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !53, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !68)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !48, line: 48, baseType: !69)
!69 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!72 = !{}
!73 = !{!74}
!74 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !75, line: 159, type: !76, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!75 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!76 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !77)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !75, line: 75, baseType: !78)
!78 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !75, line: 119, size: 512, align: 64, elements: !79)
!79 = !{!80, !84, !85, !87, !96, !101, !108, !113}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !78, file: !75, line: 121, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !75, line: 73, baseType: !83)
!83 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !75, line: 73, flags: DIFlagFwdDecl)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !78, file: !75, line: 125, baseType: !45, size: 64, align: 64, offset: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !78, file: !75, line: 131, baseType: !86, size: 64, align: 64, offset: 128)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !48, line: 122, baseType: !49)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !78, file: !75, line: 134, baseType: !88, size: 64, align: 64, offset: 192)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !75, line: 89, baseType: !89)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!37, !81, !51, !92, !93, !59, !94, !93, !59, !95}
!92 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !66)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !70)
!94 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !71)
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !78, file: !75, line: 139, baseType: !97, size: 64, align: 64, offset: 256)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !75, line: 97, baseType: !98)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{null, !81, !51}
!101 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !78, file: !75, line: 143, baseType: !102, size: 64, align: 64, offset: 320)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DISubroutineType(types: !104)
!104 = !{!105, !106}
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !78, file: !75, line: 147, baseType: !109, size: 64, align: 64, offset: 384)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DISubroutineType(types: !111)
!111 = !{!37, !81, !112, !112, !47}
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !78, file: !75, line: 152, baseType: !114, size: 64, align: 64, offset: 448)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DISubroutineType(types: !116)
!116 = !{!37, !81, !51, !38, !38}
!117 = !{i32 2, !"Dwarf Version", i32 4}
!118 = !{i32 2, !"Debug Info Version", i32 3}
!119 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!120 = !DILocalVariable(name: "filters", arg: 1, scope: !34, file: !1, line: 17, type: !38)
!121 = !DIExpression()
!122 = !DILocation(line: 17, column: 43, scope: !34)
!123 = !DILocalVariable(name: "allocator", arg: 2, scope: !34, file: !1, line: 17, type: !51)
!124 = !DILocation(line: 17, column: 68, scope: !34)
!125 = !DILocalVariable(name: "in", arg: 3, scope: !34, file: !1, line: 18, type: !66)
!126 = !DILocation(line: 18, column: 18, scope: !34)
!127 = !DILocalVariable(name: "in_pos", arg: 4, scope: !34, file: !1, line: 18, type: !70)
!128 = !DILocation(line: 18, column: 30, scope: !34)
!129 = !DILocalVariable(name: "in_size", arg: 5, scope: !34, file: !1, line: 18, type: !59)
!130 = !DILocation(line: 18, column: 45, scope: !34)
!131 = !DILocalVariable(name: "out", arg: 6, scope: !34, file: !1, line: 19, type: !71)
!132 = !DILocation(line: 19, column: 12, scope: !34)
!133 = !DILocalVariable(name: "out_pos", arg: 7, scope: !34, file: !1, line: 19, type: !70)
!134 = !DILocation(line: 19, column: 25, scope: !34)
!135 = !DILocalVariable(name: "out_size", arg: 8, scope: !34, file: !1, line: 19, type: !59)
!136 = !DILocation(line: 19, column: 41, scope: !34)
!137 = !DILocalVariable(name: "next", scope: !34, file: !1, line: 21, type: !77)
!138 = !DILocation(line: 21, column: 18, scope: !34)
!139 = !DILocation(line: 21, column: 25, scope: !34)
!140 = !DILocalVariable(name: "in_start", scope: !34, file: !1, line: 22, type: !59)
!141 = !DILocation(line: 22, column: 9, scope: !34)
!142 = !DILocalVariable(name: "out_start", scope: !34, file: !1, line: 23, type: !59)
!143 = !DILocation(line: 23, column: 9, scope: !34)
!144 = !DILocalVariable(name: "ret", scope: !34, file: !1, line: 24, type: !37)
!145 = !DILocation(line: 24, column: 11, scope: !34)
!146 = !DILocation(line: 27, column: 6, scope: !147)
!147 = distinct !DILexicalBlock(scope: !34, file: !1, line: 27, column: 6)
!148 = !DILocation(line: 27, column: 9, scope: !147)
!149 = !DILocation(line: 27, column: 17, scope: !147)
!150 = !DILocation(line: 27, column: 20, scope: !151)
!151 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!152 = !DILocation(line: 27, column: 27, scope: !151)
!153 = !DILocation(line: 27, column: 35, scope: !151)
!154 = !DILocation(line: 27, column: 39, scope: !155)
!155 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 2)
!156 = !DILocation(line: 27, column: 38, scope: !155)
!157 = !DILocation(line: 27, column: 48, scope: !155)
!158 = !DILocation(line: 27, column: 46, scope: !155)
!159 = !DILocation(line: 27, column: 56, scope: !155)
!160 = !DILocation(line: 27, column: 59, scope: !161)
!161 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 3)
!162 = !DILocation(line: 27, column: 63, scope: !161)
!163 = !DILocation(line: 28, column: 4, scope: !147)
!164 = !DILocation(line: 28, column: 7, scope: !151)
!165 = !DILocation(line: 28, column: 15, scope: !151)
!166 = !DILocation(line: 28, column: 23, scope: !151)
!167 = !DILocation(line: 28, column: 27, scope: !155)
!168 = !DILocation(line: 28, column: 26, scope: !155)
!169 = !DILocation(line: 28, column: 37, scope: !155)
!170 = !DILocation(line: 28, column: 35, scope: !155)
!171 = !DILocation(line: 27, column: 6, scope: !172)
!172 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 4)
!173 = !DILocation(line: 29, column: 3, scope: !147)
!174 = !DILocation(line: 32, column: 2, scope: !34)
!175 = !DILocalVariable(name: "ret_", scope: !176, file: !1, line: 32, type: !177)
!176 = distinct !DILexicalBlock(scope: !34, file: !1, line: 32, column: 2)
!177 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!178 = !DILocation(line: 32, column: 2, scope: !176)
!179 = !DILocation(line: 32, column: 2, scope: !180)
!180 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 1)
!181 = !DILocation(line: 32, column: 2, scope: !182)
!182 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 2)
!183 = distinct !DILexicalBlock(scope: !176, file: !1, line: 32, column: 2)
!184 = !DILocation(line: 32, column: 2, scope: !185)
!185 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 3)
!186 = !DILocation(line: 36, column: 14, scope: !34)
!187 = !DILocation(line: 36, column: 13, scope: !34)
!188 = !DILocation(line: 36, column: 11, scope: !34)
!189 = !DILocation(line: 37, column: 15, scope: !34)
!190 = !DILocation(line: 37, column: 14, scope: !34)
!191 = !DILocation(line: 37, column: 12, scope: !34)
!192 = !DILocation(line: 40, column: 13, scope: !34)
!193 = !DILocation(line: 40, column: 23, scope: !34)
!194 = !DILocation(line: 40, column: 30, scope: !34)
!195 = !DILocation(line: 40, column: 41, scope: !34)
!196 = !DILocation(line: 40, column: 45, scope: !34)
!197 = !DILocation(line: 40, column: 53, scope: !34)
!198 = !DILocation(line: 41, column: 4, scope: !34)
!199 = !DILocation(line: 41, column: 9, scope: !34)
!200 = !DILocation(line: 41, column: 18, scope: !34)
!201 = !DILocation(line: 40, column: 8, scope: !34)
!202 = !DILocation(line: 40, column: 6, scope: !34)
!203 = !DILocation(line: 43, column: 6, scope: !204)
!204 = distinct !DILexicalBlock(scope: !34, file: !1, line: 43, column: 6)
!205 = !DILocation(line: 43, column: 10, scope: !204)
!206 = !DILocation(line: 43, column: 6, scope: !34)
!207 = !DILocation(line: 44, column: 7, scope: !208)
!208 = distinct !DILexicalBlock(scope: !204, file: !1, line: 43, column: 30)
!209 = !DILocation(line: 45, column: 2, scope: !208)
!210 = !DILocation(line: 46, column: 7, scope: !211)
!211 = distinct !DILexicalBlock(scope: !212, file: !1, line: 46, column: 7)
!212 = distinct !DILexicalBlock(scope: !204, file: !1, line: 45, column: 9)
!213 = !DILocation(line: 46, column: 11, scope: !211)
!214 = !DILocation(line: 46, column: 7, scope: !212)
!215 = !DILocation(line: 49, column: 4, scope: !216)
!216 = distinct !DILexicalBlock(scope: !211, file: !1, line: 46, column: 23)
!217 = !DILocation(line: 49, column: 4, scope: !218)
!218 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 1)
!219 = !DILocation(line: 49, column: 4, scope: !220)
!220 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 2)
!221 = !DILocation(line: 49, column: 4, scope: !222)
!222 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 3)
!223 = !DILocation(line: 49, column: 4, scope: !224)
!224 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 4)
!225 = !DILocation(line: 51, column: 9, scope: !226)
!226 = distinct !DILexicalBlock(scope: !216, file: !1, line: 51, column: 8)
!227 = !DILocation(line: 51, column: 8, scope: !226)
!228 = !DILocation(line: 51, column: 19, scope: !226)
!229 = !DILocation(line: 51, column: 16, scope: !226)
!230 = !DILocation(line: 51, column: 8, scope: !216)
!231 = !DILocation(line: 55, column: 9, scope: !232)
!232 = distinct !DILexicalBlock(scope: !226, file: !1, line: 51, column: 28)
!233 = !DILocation(line: 57, column: 4, scope: !232)
!234 = !DILocation(line: 57, column: 16, scope: !235)
!235 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 1)
!236 = distinct !DILexicalBlock(scope: !226, file: !1, line: 57, column: 15)
!237 = !DILocation(line: 57, column: 15, scope: !235)
!238 = !DILocation(line: 57, column: 27, scope: !235)
!239 = !DILocation(line: 57, column: 24, scope: !235)
!240 = !DILocation(line: 60, column: 9, scope: !241)
!241 = distinct !DILexicalBlock(scope: !236, file: !1, line: 57, column: 37)
!242 = !DILocation(line: 62, column: 4, scope: !241)
!243 = !DILocalVariable(name: "tmp", scope: !244, file: !1, line: 70, type: !245)
!244 = distinct !DILexicalBlock(scope: !236, file: !1, line: 62, column: 11)
!245 = !DICompositeType(tag: DW_TAG_array_type, baseType: !68, size: 8, align: 8, elements: !246)
!246 = !{!247}
!247 = !DISubrange(count: 1)
!248 = !DILocation(line: 70, column: 13, scope: !244)
!249 = !DILocalVariable(name: "tmp_pos", scope: !244, file: !1, line: 71, type: !59)
!250 = !DILocation(line: 71, column: 12, scope: !244)
!251 = !DILocation(line: 72, column: 16, scope: !244)
!252 = !DILocation(line: 72, column: 26, scope: !244)
!253 = !DILocation(line: 72, column: 33, scope: !244)
!254 = !DILocation(line: 73, column: 7, scope: !244)
!255 = !DILocation(line: 73, column: 11, scope: !244)
!256 = !DILocation(line: 73, column: 19, scope: !244)
!257 = !DILocation(line: 74, column: 7, scope: !244)
!258 = !DILocation(line: 72, column: 11, scope: !244)
!259 = !DILocation(line: 76, column: 9, scope: !260)
!260 = distinct !DILexicalBlock(scope: !244, file: !1, line: 76, column: 9)
!261 = !DILocation(line: 76, column: 17, scope: !260)
!262 = !DILocation(line: 76, column: 9, scope: !244)
!263 = !DILocation(line: 77, column: 10, scope: !260)
!264 = !DILocation(line: 77, column: 6, scope: !260)
!265 = !DILocation(line: 79, column: 10, scope: !260)
!266 = !DILocation(line: 81, column: 3, scope: !216)
!267 = !DILocation(line: 84, column: 13, scope: !212)
!268 = !DILocation(line: 84, column: 4, scope: !212)
!269 = !DILocation(line: 84, column: 11, scope: !212)
!270 = !DILocation(line: 85, column: 14, scope: !212)
!271 = !DILocation(line: 85, column: 4, scope: !212)
!272 = !DILocation(line: 85, column: 12, scope: !212)
!273 = !DILocation(line: 88, column: 23, scope: !34)
!274 = !DILocation(line: 88, column: 2, scope: !34)
!275 = !DILocation(line: 90, column: 9, scope: !34)
!276 = !DILocation(line: 90, column: 2, scope: !34)
!277 = !DILocation(line: 91, column: 1, scope: !34)
