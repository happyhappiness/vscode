; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_buffer_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [43 x i8] c"*in_pos == in_size || *out_pos == out_size\00", align 1
@.str.1 = private unnamed_addr constant [93 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_buffer_decoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_stream_buffer_decode = private unnamed_addr constant [139 x i8] c"lzma_ret lzma_stream_buffer_decode(uint64_t *, uint32_t, lzma_allocator *, const uint8_t *, size_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_buffer_decode(i64* %memlimit, i32 %flags, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %memlimit.addr = alloca i64*, align 8
  %flags.addr = alloca i32, align 4
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %stream_decoder = alloca %struct.lzma_next_coder_s, align 8
  %ret = alloca i32, align 4
  %in_start = alloca i64, align 8
  %out_start = alloca i64, align 8
  %memusage = alloca i64, align 8
  store i64* %memlimit, i64** %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memlimit.addr, metadata !122, metadata !123), !dbg !124
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !125, metadata !123), !dbg !126
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !127, metadata !123), !dbg !128
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !129, metadata !123), !dbg !130
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !131, metadata !123), !dbg !132
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !133, metadata !123), !dbg !134
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !135, metadata !123), !dbg !136
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !137, metadata !123), !dbg !138
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !139, metadata !123), !dbg !140
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s* %stream_decoder, metadata !141, metadata !123), !dbg !142
  %0 = bitcast %struct.lzma_next_coder_s* %stream_decoder to i8*, !dbg !143
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !143
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !144, metadata !123), !dbg !145
  %1 = load i64*, i64** %in_pos.addr, align 8, !dbg !146
  %cmp = icmp eq i64* %1, null, !dbg !148
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !149

lor.lhs.false:                                    ; preds = %entry
  %2 = load i8*, i8** %in.addr, align 8, !dbg !150
  %cmp1 = icmp eq i8* %2, null, !dbg !152
  br i1 %cmp1, label %land.lhs.true, label %lor.lhs.false3, !dbg !153

land.lhs.true:                                    ; preds = %lor.lhs.false
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !154
  %4 = load i64, i64* %3, align 8, !dbg !156
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !157
  %cmp2 = icmp ne i64 %4, %5, !dbg !158
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !159

lor.lhs.false3:                                   ; preds = %land.lhs.true, %lor.lhs.false
  %6 = load i64*, i64** %in_pos.addr, align 8, !dbg !160
  %7 = load i64, i64* %6, align 8, !dbg !161
  %8 = load i64, i64* %in_size.addr, align 8, !dbg !162
  %cmp4 = icmp ugt i64 %7, %8, !dbg !163
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !164

lor.lhs.false5:                                   ; preds = %lor.lhs.false3
  %9 = load i64*, i64** %out_pos.addr, align 8, !dbg !165
  %cmp6 = icmp eq i64* %9, null, !dbg !166
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !167

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %10 = load i8*, i8** %out.addr, align 8, !dbg !168
  %cmp8 = icmp eq i8* %10, null, !dbg !169
  br i1 %cmp8, label %land.lhs.true9, label %lor.lhs.false11, !dbg !170

land.lhs.true9:                                   ; preds = %lor.lhs.false7
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !171
  %12 = load i64, i64* %11, align 8, !dbg !172
  %13 = load i64, i64* %out_size.addr, align 8, !dbg !173
  %cmp10 = icmp ne i64 %12, %13, !dbg !174
  br i1 %cmp10, label %if.then, label %lor.lhs.false11, !dbg !175

lor.lhs.false11:                                  ; preds = %land.lhs.true9, %lor.lhs.false7
  %14 = load i64*, i64** %out_pos.addr, align 8, !dbg !176
  %15 = load i64, i64* %14, align 8, !dbg !177
  %16 = load i64, i64* %out_size.addr, align 8, !dbg !178
  %cmp12 = icmp ugt i64 %15, %16, !dbg !179
  br i1 %cmp12, label %if.then, label %if.end, !dbg !180

if.then:                                          ; preds = %lor.lhs.false11, %land.lhs.true9, %lor.lhs.false5, %lor.lhs.false3, %land.lhs.true, %entry
  store i32 11, i32* %retval, align 4, !dbg !182
  br label %return, !dbg !182

if.end:                                           ; preds = %lor.lhs.false11
  %17 = load i32, i32* %flags.addr, align 4, !dbg !183
  %and = and i32 %17, 4, !dbg !185
  %tobool = icmp ne i32 %and, 0, !dbg !185
  br i1 %tobool, label %if.then13, label %if.end14, !dbg !186

if.then13:                                        ; preds = %if.end
  store i32 11, i32* %retval, align 4, !dbg !187
  br label %return, !dbg !187

if.end14:                                         ; preds = %if.end
  %18 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !188
  %19 = load i64*, i64** %memlimit.addr, align 8, !dbg !189
  %20 = load i64, i64* %19, align 8, !dbg !190
  %21 = load i32, i32* %flags.addr, align 4, !dbg !191
  %call = call i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s* %stream_decoder, %struct.lzma_allocator* %18, i64 %20, i32 %21), !dbg !192
  store i32 %call, i32* %ret, align 4, !dbg !193
  %22 = load i32, i32* %ret, align 4, !dbg !194
  %cmp15 = icmp eq i32 %22, 0, !dbg !196
  br i1 %cmp15, label %if.then16, label %if.end37, !dbg !197

if.then16:                                        ; preds = %if.end14
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !198, metadata !123), !dbg !201
  %23 = load i64*, i64** %in_pos.addr, align 8, !dbg !202
  %24 = load i64, i64* %23, align 8, !dbg !203
  store i64 %24, i64* %in_start, align 8, !dbg !201
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !204, metadata !123), !dbg !205
  %25 = load i64*, i64** %out_pos.addr, align 8, !dbg !206
  %26 = load i64, i64* %25, align 8, !dbg !207
  store i64 %26, i64* %out_start, align 8, !dbg !205
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %stream_decoder, i32 0, i32 3, !dbg !208
  %27 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !208
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %stream_decoder, i32 0, i32 0, !dbg !209
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !209
  %29 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !210
  %30 = load i8*, i8** %in.addr, align 8, !dbg !211
  %31 = load i64*, i64** %in_pos.addr, align 8, !dbg !212
  %32 = load i64, i64* %in_size.addr, align 8, !dbg !213
  %33 = load i8*, i8** %out.addr, align 8, !dbg !214
  %34 = load i64*, i64** %out_pos.addr, align 8, !dbg !215
  %35 = load i64, i64* %out_size.addr, align 8, !dbg !216
  %call17 = call i32 %27(%struct.lzma_coder_s* %28, %struct.lzma_allocator* %29, i8* %30, i64* %31, i64 %32, i8* %33, i64* %34, i64 %35, i32 3), !dbg !217
  store i32 %call17, i32* %ret, align 4, !dbg !218
  %36 = load i32, i32* %ret, align 4, !dbg !219
  %cmp18 = icmp eq i32 %36, 1, !dbg !221
  br i1 %cmp18, label %if.then19, label %if.else, !dbg !222

if.then19:                                        ; preds = %if.then16
  store i32 0, i32* %ret, align 4, !dbg !223
  br label %if.end36, !dbg !225

if.else:                                          ; preds = %if.then16
  %37 = load i64, i64* %in_start, align 8, !dbg !226
  %38 = load i64*, i64** %in_pos.addr, align 8, !dbg !228
  store i64 %37, i64* %38, align 8, !dbg !229
  %39 = load i64, i64* %out_start, align 8, !dbg !230
  %40 = load i64*, i64** %out_pos.addr, align 8, !dbg !231
  store i64 %39, i64* %40, align 8, !dbg !232
  %41 = load i32, i32* %ret, align 4, !dbg !233
  %cmp20 = icmp eq i32 %41, 0, !dbg !235
  br i1 %cmp20, label %if.then21, label %if.else29, !dbg !236

if.then21:                                        ; preds = %if.else
  %42 = load i64*, i64** %in_pos.addr, align 8, !dbg !237
  %43 = load i64, i64* %42, align 8, !dbg !237
  %44 = load i64, i64* %in_size.addr, align 8, !dbg !237
  %cmp22 = icmp eq i64 %43, %44, !dbg !237
  br i1 %cmp22, label %cond.true, label %lor.lhs.false23, !dbg !237

lor.lhs.false23:                                  ; preds = %if.then21
  %45 = load i64*, i64** %out_pos.addr, align 8, !dbg !239
  %46 = load i64, i64* %45, align 8, !dbg !239
  %47 = load i64, i64* %out_size.addr, align 8, !dbg !239
  %cmp24 = icmp eq i64 %46, %47, !dbg !239
  br i1 %cmp24, label %cond.true, label %cond.false, !dbg !239

cond.true:                                        ; preds = %lor.lhs.false23, %if.then21
  br label %cond.end, !dbg !241

cond.false:                                       ; preds = %lor.lhs.false23
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([93 x i8], [93 x i8]* @.str.1, i32 0, i32 0), i32 64, i8* getelementptr inbounds ([139 x i8], [139 x i8]* @__PRETTY_FUNCTION__.lzma_stream_buffer_decode, i32 0, i32 0)) #5, !dbg !243
  unreachable, !dbg !243
                                                  ; No predecessors!
  br label %cond.end, !dbg !245

cond.end:                                         ; preds = %48, %cond.true
  %49 = load i64*, i64** %in_pos.addr, align 8, !dbg !247
  %50 = load i64, i64* %49, align 8, !dbg !249
  %51 = load i64, i64* %in_size.addr, align 8, !dbg !250
  %cmp25 = icmp eq i64 %50, %51, !dbg !251
  br i1 %cmp25, label %if.then26, label %if.else27, !dbg !252

if.then26:                                        ; preds = %cond.end
  store i32 9, i32* %ret, align 4, !dbg !253
  br label %if.end28, !dbg !254

if.else27:                                        ; preds = %cond.end
  store i32 10, i32* %ret, align 4, !dbg !255
  br label %if.end28

if.end28:                                         ; preds = %if.else27, %if.then26
  br label %if.end35, !dbg !256

if.else29:                                        ; preds = %if.else
  %52 = load i32, i32* %ret, align 4, !dbg !257
  %cmp30 = icmp eq i32 %52, 6, !dbg !260
  br i1 %cmp30, label %if.then31, label %if.end34, !dbg !257

if.then31:                                        ; preds = %if.else29
  call void @llvm.dbg.declare(metadata i64* %memusage, metadata !261, metadata !123), !dbg !263
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %stream_decoder, i32 0, i32 6, !dbg !264
  %53 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !264
  %coder32 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %stream_decoder, i32 0, i32 0, !dbg !265
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder32, align 8, !dbg !265
  %55 = load i64*, i64** %memlimit.addr, align 8, !dbg !266
  %call33 = call i32 %53(%struct.lzma_coder_s* %54, i64* %55, i64* %memusage, i64 0), !dbg !267
  br label %if.end34, !dbg !268

if.end34:                                         ; preds = %if.then31, %if.else29
  br label %if.end35

if.end35:                                         ; preds = %if.end34, %if.end28
  br label %if.end36

if.end36:                                         ; preds = %if.end35, %if.then19
  br label %if.end37, !dbg !269

if.end37:                                         ; preds = %if.end36, %if.end14
  %56 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !270
  call void @lzma_next_end(%struct.lzma_next_coder_s* %stream_decoder, %struct.lzma_allocator* %56), !dbg !271
  %57 = load i32, i32* %ret, align 4, !dbg !272
  store i32 %57, i32* %retval, align 4, !dbg !273
  br label %return, !dbg !273

return:                                           ; preds = %if.end37, %if.then13, %if.then
  %58 = load i32, i32* %retval, align 4, !dbg !274
  ret i32 %58, !dbg !274
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32) #3

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
!llvm.module.flags = !{!119, !120}
!llvm.ident = !{!121}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !33, globals: !66)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_buffer_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!34 = distinct !DISubprogram(name: "lzma_stream_buffer_decode", scope: !1, file: !1, line: 17, type: !35, isLocal: false, isDefinition: true, scopeLine: 21, flags: DIFlagPrototyped, isOptimized: false, variables: !65)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !42, !44, !59, !63, !52, !64, !63, !52}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !40, line: 55, baseType: !41)
!40 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!41 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !40, line: 51, baseType: !43)
!43 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !46)
!46 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !47)
!47 = !{!48, !54, !58}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !46, file: !4, line: 376, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!32, !32, !52, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !53, line: 62, baseType: !41)
!53 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !46, file: !4, line: 390, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !32, !32}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !46, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !61)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !40, line: 48, baseType: !62)
!62 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!65 = !{}
!66 = !{!67}
!67 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !68, line: 159, type: !69, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!68 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !70)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !68, line: 75, baseType: !71)
!71 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !68, line: 119, size: 512, align: 64, elements: !72)
!72 = !{!73, !77, !80, !82, !91, !96, !103, !107}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !71, file: !68, line: 121, baseType: !74, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !68, line: 73, baseType: !76)
!76 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !68, line: 73, flags: DIFlagFwdDecl)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !71, file: !68, line: 125, baseType: !78, size: 64, align: 64, offset: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !79, line: 63, baseType: !39)
!79 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!80 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !71, file: !68, line: 131, baseType: !81, size: 64, align: 64, offset: 128)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !40, line: 122, baseType: !41)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !71, file: !68, line: 134, baseType: !83, size: 64, align: 64, offset: 192)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !68, line: 89, baseType: !84)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DISubroutineType(types: !86)
!86 = !{!37, !74, !44, !87, !88, !52, !89, !88, !52, !90}
!87 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !59)
!88 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !63)
!89 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !64)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !71, file: !68, line: 139, baseType: !92, size: 64, align: 64, offset: 256)
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !68, line: 97, baseType: !93)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{null, !74, !44}
!96 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !71, file: !68, line: 143, baseType: !97, size: 64, align: 64, offset: 320)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DISubroutineType(types: !99)
!99 = !{!100, !101}
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !75)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !71, file: !68, line: 147, baseType: !104, size: 64, align: 64, offset: 384)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!37, !74, !38, !38, !39}
!107 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !71, file: !68, line: 152, baseType: !108, size: 64, align: 64, offset: 448)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DISubroutineType(types: !110)
!110 = !{!37, !74, !44, !111, !111}
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !113)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !114, line: 65, baseType: !115)
!114 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!115 = !DICompositeType(tag: DW_TAG_structure_type, file: !114, line: 43, size: 128, align: 64, elements: !116)
!116 = !{!117, !118}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !115, file: !114, line: 54, baseType: !78, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !115, file: !114, line: 63, baseType: !32, size: 64, align: 64, offset: 64)
!119 = !{i32 2, !"Dwarf Version", i32 4}
!120 = !{i32 2, !"Debug Info Version", i32 3}
!121 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!122 = !DILocalVariable(name: "memlimit", arg: 1, scope: !34, file: !1, line: 17, type: !38)
!123 = !DIExpression()
!124 = !DILocation(line: 17, column: 37, scope: !34)
!125 = !DILocalVariable(name: "flags", arg: 2, scope: !34, file: !1, line: 17, type: !42)
!126 = !DILocation(line: 17, column: 56, scope: !34)
!127 = !DILocalVariable(name: "allocator", arg: 3, scope: !34, file: !1, line: 18, type: !44)
!128 = !DILocation(line: 18, column: 19, scope: !34)
!129 = !DILocalVariable(name: "in", arg: 4, scope: !34, file: !1, line: 19, type: !59)
!130 = !DILocation(line: 19, column: 18, scope: !34)
!131 = !DILocalVariable(name: "in_pos", arg: 5, scope: !34, file: !1, line: 19, type: !63)
!132 = !DILocation(line: 19, column: 30, scope: !34)
!133 = !DILocalVariable(name: "in_size", arg: 6, scope: !34, file: !1, line: 19, type: !52)
!134 = !DILocation(line: 19, column: 45, scope: !34)
!135 = !DILocalVariable(name: "out", arg: 7, scope: !34, file: !1, line: 20, type: !64)
!136 = !DILocation(line: 20, column: 12, scope: !34)
!137 = !DILocalVariable(name: "out_pos", arg: 8, scope: !34, file: !1, line: 20, type: !63)
!138 = !DILocation(line: 20, column: 25, scope: !34)
!139 = !DILocalVariable(name: "out_size", arg: 9, scope: !34, file: !1, line: 20, type: !52)
!140 = !DILocation(line: 20, column: 41, scope: !34)
!141 = !DILocalVariable(name: "stream_decoder", scope: !34, file: !1, line: 22, type: !70)
!142 = !DILocation(line: 22, column: 18, scope: !34)
!143 = !DILocation(line: 22, column: 35, scope: !34)
!144 = !DILocalVariable(name: "ret", scope: !34, file: !1, line: 23, type: !37)
!145 = !DILocation(line: 23, column: 11, scope: !34)
!146 = !DILocation(line: 26, column: 6, scope: !147)
!147 = distinct !DILexicalBlock(scope: !34, file: !1, line: 26, column: 6)
!148 = !DILocation(line: 26, column: 13, scope: !147)
!149 = !DILocation(line: 26, column: 21, scope: !147)
!150 = !DILocation(line: 26, column: 25, scope: !151)
!151 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!152 = !DILocation(line: 26, column: 28, scope: !151)
!153 = !DILocation(line: 26, column: 36, scope: !151)
!154 = !DILocation(line: 26, column: 40, scope: !155)
!155 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 2)
!156 = !DILocation(line: 26, column: 39, scope: !155)
!157 = !DILocation(line: 26, column: 50, scope: !155)
!158 = !DILocation(line: 26, column: 47, scope: !155)
!159 = !DILocation(line: 27, column: 4, scope: !147)
!160 = !DILocation(line: 27, column: 8, scope: !151)
!161 = !DILocation(line: 27, column: 7, scope: !151)
!162 = !DILocation(line: 27, column: 17, scope: !151)
!163 = !DILocation(line: 27, column: 15, scope: !151)
!164 = !DILocation(line: 27, column: 25, scope: !151)
!165 = !DILocation(line: 27, column: 28, scope: !155)
!166 = !DILocation(line: 27, column: 36, scope: !155)
!167 = !DILocation(line: 28, column: 4, scope: !147)
!168 = !DILocation(line: 28, column: 8, scope: !151)
!169 = !DILocation(line: 28, column: 12, scope: !151)
!170 = !DILocation(line: 28, column: 20, scope: !151)
!171 = !DILocation(line: 28, column: 24, scope: !155)
!172 = !DILocation(line: 28, column: 23, scope: !155)
!173 = !DILocation(line: 28, column: 35, scope: !155)
!174 = !DILocation(line: 28, column: 32, scope: !155)
!175 = !DILocation(line: 29, column: 4, scope: !147)
!176 = !DILocation(line: 29, column: 8, scope: !151)
!177 = !DILocation(line: 29, column: 7, scope: !151)
!178 = !DILocation(line: 29, column: 18, scope: !151)
!179 = !DILocation(line: 29, column: 16, scope: !151)
!180 = !DILocation(line: 26, column: 6, scope: !181)
!181 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 3)
!182 = !DILocation(line: 30, column: 3, scope: !147)
!183 = !DILocation(line: 33, column: 6, scope: !184)
!184 = distinct !DILexicalBlock(scope: !34, file: !1, line: 33, column: 6)
!185 = !DILocation(line: 33, column: 12, scope: !184)
!186 = !DILocation(line: 33, column: 6, scope: !34)
!187 = !DILocation(line: 34, column: 3, scope: !184)
!188 = !DILocation(line: 40, column: 21, scope: !34)
!189 = !DILocation(line: 40, column: 33, scope: !34)
!190 = !DILocation(line: 40, column: 32, scope: !34)
!191 = !DILocation(line: 40, column: 43, scope: !34)
!192 = !DILocation(line: 39, column: 8, scope: !34)
!193 = !DILocation(line: 39, column: 6, scope: !34)
!194 = !DILocation(line: 42, column: 6, scope: !195)
!195 = distinct !DILexicalBlock(scope: !34, file: !1, line: 42, column: 6)
!196 = !DILocation(line: 42, column: 10, scope: !195)
!197 = !DILocation(line: 42, column: 6, scope: !34)
!198 = !DILocalVariable(name: "in_start", scope: !199, file: !1, line: 45, type: !200)
!199 = distinct !DILexicalBlock(scope: !195, file: !1, line: 42, column: 22)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !52)
!201 = !DILocation(line: 45, column: 16, scope: !199)
!202 = !DILocation(line: 45, column: 28, scope: !199)
!203 = !DILocation(line: 45, column: 27, scope: !199)
!204 = !DILocalVariable(name: "out_start", scope: !199, file: !1, line: 46, type: !200)
!205 = !DILocation(line: 46, column: 16, scope: !199)
!206 = !DILocation(line: 46, column: 29, scope: !199)
!207 = !DILocation(line: 46, column: 28, scope: !199)
!208 = !DILocation(line: 49, column: 24, scope: !199)
!209 = !DILocation(line: 49, column: 44, scope: !199)
!210 = !DILocation(line: 49, column: 51, scope: !199)
!211 = !DILocation(line: 50, column: 5, scope: !199)
!212 = !DILocation(line: 50, column: 9, scope: !199)
!213 = !DILocation(line: 50, column: 17, scope: !199)
!214 = !DILocation(line: 50, column: 26, scope: !199)
!215 = !DILocation(line: 50, column: 31, scope: !199)
!216 = !DILocation(line: 50, column: 40, scope: !199)
!217 = !DILocation(line: 49, column: 9, scope: !199)
!218 = !DILocation(line: 49, column: 7, scope: !199)
!219 = !DILocation(line: 53, column: 7, scope: !220)
!220 = distinct !DILexicalBlock(scope: !199, file: !1, line: 53, column: 7)
!221 = !DILocation(line: 53, column: 11, scope: !220)
!222 = !DILocation(line: 53, column: 7, scope: !199)
!223 = !DILocation(line: 54, column: 8, scope: !224)
!224 = distinct !DILexicalBlock(scope: !220, file: !1, line: 53, column: 31)
!225 = !DILocation(line: 55, column: 3, scope: !224)
!226 = !DILocation(line: 57, column: 14, scope: !227)
!227 = distinct !DILexicalBlock(scope: !220, file: !1, line: 55, column: 10)
!228 = !DILocation(line: 57, column: 5, scope: !227)
!229 = !DILocation(line: 57, column: 12, scope: !227)
!230 = !DILocation(line: 58, column: 15, scope: !227)
!231 = !DILocation(line: 58, column: 5, scope: !227)
!232 = !DILocation(line: 58, column: 13, scope: !227)
!233 = !DILocation(line: 60, column: 8, scope: !234)
!234 = distinct !DILexicalBlock(scope: !227, file: !1, line: 60, column: 8)
!235 = !DILocation(line: 60, column: 12, scope: !234)
!236 = !DILocation(line: 60, column: 8, scope: !227)
!237 = !DILocation(line: 63, column: 5, scope: !238)
!238 = distinct !DILexicalBlock(scope: !234, file: !1, line: 60, column: 24)
!239 = !DILocation(line: 63, column: 5, scope: !240)
!240 = !DILexicalBlockFile(scope: !238, file: !1, discriminator: 1)
!241 = !DILocation(line: 63, column: 5, scope: !242)
!242 = !DILexicalBlockFile(scope: !238, file: !1, discriminator: 2)
!243 = !DILocation(line: 63, column: 5, scope: !244)
!244 = !DILexicalBlockFile(scope: !238, file: !1, discriminator: 3)
!245 = !DILocation(line: 63, column: 5, scope: !246)
!246 = !DILexicalBlockFile(scope: !238, file: !1, discriminator: 4)
!247 = !DILocation(line: 71, column: 10, scope: !248)
!248 = distinct !DILexicalBlock(scope: !238, file: !1, line: 71, column: 9)
!249 = !DILocation(line: 71, column: 9, scope: !248)
!250 = !DILocation(line: 71, column: 20, scope: !248)
!251 = !DILocation(line: 71, column: 17, scope: !248)
!252 = !DILocation(line: 71, column: 9, scope: !238)
!253 = !DILocation(line: 72, column: 10, scope: !248)
!254 = !DILocation(line: 72, column: 6, scope: !248)
!255 = !DILocation(line: 74, column: 10, scope: !248)
!256 = !DILocation(line: 76, column: 4, scope: !238)
!257 = !DILocation(line: 76, column: 15, scope: !258)
!258 = !DILexicalBlockFile(scope: !259, file: !1, discriminator: 1)
!259 = distinct !DILexicalBlock(scope: !234, file: !1, line: 76, column: 15)
!260 = !DILocation(line: 76, column: 19, scope: !258)
!261 = !DILocalVariable(name: "memusage", scope: !262, file: !1, line: 79, type: !39)
!262 = distinct !DILexicalBlock(scope: !259, file: !1, line: 76, column: 43)
!263 = !DILocation(line: 79, column: 14, scope: !262)
!264 = !DILocation(line: 80, column: 26, scope: !262)
!265 = !DILocation(line: 81, column: 22, scope: !262)
!266 = !DILocation(line: 82, column: 7, scope: !262)
!267 = !DILocation(line: 80, column: 11, scope: !262)
!268 = !DILocation(line: 83, column: 4, scope: !262)
!269 = !DILocation(line: 85, column: 2, scope: !199)
!270 = !DILocation(line: 90, column: 33, scope: !34)
!271 = !DILocation(line: 90, column: 2, scope: !34)
!272 = !DILocation(line: 92, column: 9, scope: !34)
!273 = !DILocation(line: 92, column: 2, scope: !34)
!274 = !DILocation(line: 93, column: 1, scope: !34)
