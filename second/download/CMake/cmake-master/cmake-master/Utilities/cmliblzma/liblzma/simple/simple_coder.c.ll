; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_coder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i8, i8, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, %struct.lzma_simple_s*, i32, i64, i64, i64, i64, [0 x i8] }
%struct.lzma_simple_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i8* }
%struct.lzma_options_bcj = type { i32 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [31 x i8] c"coder->filtered == coder->size\00", align 1
@.str.1 = private unnamed_addr constant [84 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_coder.c\00", align 1
@__PRETTY_FUNCTION__.simple_code = private unnamed_addr constant [162 x i8] c"lzma_ret simple_code(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.2 = private unnamed_addr constant [24 x i8] c"!coder->end_was_reached\00", align 1
@.str.3 = private unnamed_addr constant [23 x i8] c"ret != LZMA_STREAM_END\00", align 1
@.str.4 = private unnamed_addr constant [35 x i8] c"unfiltered <= coder->allocated / 2\00", align 1
@.str.5 = private unnamed_addr constant [16 x i8] c"coder->pos == 0\00", align 1
@__PRETTY_FUNCTION__.copy_or_code = private unnamed_addr constant [163 x i8] c"lzma_ret copy_or_code(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.6 = private unnamed_addr constant [44 x i8] c"!coder->is_encoder || action == LZMA_FINISH\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)* %filter, i64 %simple_size, i64 %unfiltered_max, i32 %alignment, i1 zeroext %is_encoder) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %filter.addr = alloca i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, align 8
  %simple_size.addr = alloca i64, align 8
  %unfiltered_max.addr = alloca i64, align 8
  %alignment.addr = alloca i32, align 4
  %is_encoder.addr = alloca i8, align 1
  %simple26 = alloca %struct.lzma_options_bcj*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !165, metadata !166), !dbg !167
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !168, metadata !166), !dbg !169
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !170, metadata !166), !dbg !171
  store i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)* %filter, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)** %filter.addr, metadata !172, metadata !166), !dbg !173
  store i64 %simple_size, i64* %simple_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %simple_size.addr, metadata !174, metadata !166), !dbg !175
  store i64 %unfiltered_max, i64* %unfiltered_max.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unfiltered_max.addr, metadata !176, metadata !166), !dbg !177
  store i32 %alignment, i32* %alignment.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %alignment.addr, metadata !178, metadata !166), !dbg !179
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !180, metadata !166), !dbg !181
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !182
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 0, !dbg !184
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !184
  %cmp = icmp eq %struct.lzma_coder_s* %1, null, !dbg !185
  br i1 %cmp, label %if.then, label %if.end23, !dbg !186

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %unfiltered_max.addr, align 8, !dbg !187
  %mul = mul i64 2, %2, !dbg !189
  %add = add i64 128, %mul, !dbg !190
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !191
  %call = call noalias i8* @lzma_alloc(i64 %add, %struct.lzma_allocator* %3), !dbg !192
  %4 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !192
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !193
  %coder1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %5, i32 0, i32 0, !dbg !194
  store %struct.lzma_coder_s* %4, %struct.lzma_coder_s** %coder1, align 8, !dbg !195
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !196
  %coder2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 0, !dbg !198
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !198
  %cmp3 = icmp eq %struct.lzma_coder_s* %7, null, !dbg !199
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !200

if.then4:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !201
  br label %return, !dbg !201

if.end:                                           ; preds = %if.then
  %8 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !202
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %8, i32 0, i32 3, !dbg !203
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @simple_code, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !204
  %9 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !205
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %9, i32 0, i32 4, !dbg !206
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @simple_coder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !207
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !208
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 7, !dbg !209
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* @simple_coder_update, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !210
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !211
  %coder5 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !212
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !212
  %next6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !213
  %13 = bitcast %struct.lzma_next_coder_s* %next6 to i8*, !dbg !214
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !214
  %14 = load i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)** %filter.addr, align 8, !dbg !215
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !216
  %coder7 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 0, !dbg !217
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder7, align 8, !dbg !217
  %filter8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 3, !dbg !218
  store i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)* %14, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)** %filter8, align 8, !dbg !219
  %17 = load i64, i64* %unfiltered_max.addr, align 8, !dbg !220
  %mul9 = mul i64 2, %17, !dbg !221
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !222
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 0, !dbg !223
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !223
  %allocated = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 6, !dbg !224
  store i64 %mul9, i64* %allocated, align 8, !dbg !225
  %20 = load i64, i64* %simple_size.addr, align 8, !dbg !226
  %cmp11 = icmp ugt i64 %20, 0, !dbg !228
  br i1 %cmp11, label %if.then12, label %if.else, !dbg !229

if.then12:                                        ; preds = %if.end
  %21 = load i64, i64* %simple_size.addr, align 8, !dbg !230
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !232
  %call13 = call noalias i8* @lzma_alloc(i64 %21, %struct.lzma_allocator* %22), !dbg !233
  %23 = bitcast i8* %call13 to %struct.lzma_simple_s*, !dbg !233
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !234
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !235
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !235
  %simple = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 4, !dbg !236
  store %struct.lzma_simple_s* %23, %struct.lzma_simple_s** %simple, align 8, !dbg !237
  %26 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !238
  %coder15 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %26, i32 0, i32 0, !dbg !240
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder15, align 8, !dbg !240
  %simple16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 4, !dbg !241
  %28 = load %struct.lzma_simple_s*, %struct.lzma_simple_s** %simple16, align 8, !dbg !241
  %cmp17 = icmp eq %struct.lzma_simple_s* %28, null, !dbg !242
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !243

if.then18:                                        ; preds = %if.then12
  store i32 5, i32* %retval, align 4, !dbg !244
  br label %return, !dbg !244

if.end19:                                         ; preds = %if.then12
  br label %if.end22, !dbg !245

if.else:                                          ; preds = %if.end
  %29 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !246
  %coder20 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %29, i32 0, i32 0, !dbg !248
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !248
  %simple21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 4, !dbg !249
  store %struct.lzma_simple_s* null, %struct.lzma_simple_s** %simple21, align 8, !dbg !250
  br label %if.end22

if.end22:                                         ; preds = %if.else, %if.end19
  br label %if.end23, !dbg !251

if.end23:                                         ; preds = %if.end22, %entry
  %31 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !252
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %31, i64 0, !dbg !252
  %options = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 2, !dbg !254
  %32 = load i8*, i8** %options, align 8, !dbg !254
  %cmp24 = icmp ne i8* %32, null, !dbg !255
  br i1 %cmp24, label %if.then25, label %if.else34, !dbg !256

if.then25:                                        ; preds = %if.end23
  call void @llvm.dbg.declare(metadata %struct.lzma_options_bcj** %simple26, metadata !257, metadata !166), !dbg !266
  %33 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !267
  %arrayidx27 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %33, i64 0, !dbg !267
  %options28 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx27, i32 0, i32 2, !dbg !268
  %34 = load i8*, i8** %options28, align 8, !dbg !268
  %35 = bitcast i8* %34 to %struct.lzma_options_bcj*, !dbg !267
  store %struct.lzma_options_bcj* %35, %struct.lzma_options_bcj** %simple26, align 8, !dbg !266
  %36 = load %struct.lzma_options_bcj*, %struct.lzma_options_bcj** %simple26, align 8, !dbg !269
  %start_offset = getelementptr inbounds %struct.lzma_options_bcj, %struct.lzma_options_bcj* %36, i32 0, i32 0, !dbg !270
  %37 = load i32, i32* %start_offset, align 4, !dbg !270
  %38 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !271
  %coder29 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %38, i32 0, i32 0, !dbg !272
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder29, align 8, !dbg !272
  %now_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 5, !dbg !273
  store i32 %37, i32* %now_pos, align 8, !dbg !274
  %40 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !275
  %coder30 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %40, i32 0, i32 0, !dbg !277
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder30, align 8, !dbg !277
  %now_pos31 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 5, !dbg !278
  %42 = load i32, i32* %now_pos31, align 8, !dbg !278
  %43 = load i32, i32* %alignment.addr, align 4, !dbg !279
  %sub = sub i32 %43, 1, !dbg !280
  %and = and i32 %42, %sub, !dbg !281
  %tobool = icmp ne i32 %and, 0, !dbg !281
  br i1 %tobool, label %if.then32, label %if.end33, !dbg !282

if.then32:                                        ; preds = %if.then25
  store i32 8, i32* %retval, align 4, !dbg !283
  br label %return, !dbg !283

if.end33:                                         ; preds = %if.then25
  br label %if.end37, !dbg !284

if.else34:                                        ; preds = %if.end23
  %44 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !285
  %coder35 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %44, i32 0, i32 0, !dbg !287
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder35, align 8, !dbg !287
  %now_pos36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 5, !dbg !288
  store i32 0, i32* %now_pos36, align 8, !dbg !289
  br label %if.end37

if.end37:                                         ; preds = %if.else34, %if.end33
  %46 = load i8, i8* %is_encoder.addr, align 1, !dbg !290
  %tobool38 = trunc i8 %46 to i1, !dbg !290
  %47 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !291
  %coder39 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %47, i32 0, i32 0, !dbg !292
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder39, align 8, !dbg !292
  %is_encoder40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 2, !dbg !293
  %frombool41 = zext i1 %tobool38 to i8, !dbg !294
  store i8 %frombool41, i8* %is_encoder40, align 1, !dbg !294
  %49 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !295
  %coder42 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %49, i32 0, i32 0, !dbg !296
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder42, align 8, !dbg !296
  %end_was_reached = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 1, !dbg !297
  store i8 0, i8* %end_was_reached, align 8, !dbg !298
  %51 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !299
  %coder43 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %51, i32 0, i32 0, !dbg !300
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder43, align 8, !dbg !300
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 7, !dbg !301
  store i64 0, i64* %pos, align 8, !dbg !302
  %53 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !303
  %coder44 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %53, i32 0, i32 0, !dbg !304
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder44, align 8, !dbg !304
  %filtered = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 8, !dbg !305
  store i64 0, i64* %filtered, align 8, !dbg !306
  %55 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !307
  %coder45 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %55, i32 0, i32 0, !dbg !308
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder45, align 8, !dbg !308
  %size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 9, !dbg !309
  store i64 0, i64* %size, align 8, !dbg !310
  %57 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !311
  %coder46 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %57, i32 0, i32 0, !dbg !312
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder46, align 8, !dbg !312
  %next47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 0, !dbg !313
  %59 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !314
  %60 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !315
  %add.ptr = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %60, i64 1, !dbg !316
  %call48 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next47, %struct.lzma_allocator* %59, %struct.lzma_filter_info_s* %add.ptr), !dbg !317
  store i32 %call48, i32* %retval, align 4, !dbg !318
  br label %return, !dbg !318

return:                                           ; preds = %if.end37, %if.then32, %if.then18, %if.then4
  %61 = load i32, i32* %retval, align 4, !dbg !319
  ret i32 %61, !dbg !319
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @simple_code(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !152 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %out_avail = alloca i64, align 8
  %buf_avail = alloca i64, align 8
  %size27 = alloca i64, align 8
  %filtered28 = alloca i64, align 8
  %unfiltered = alloca i64, align 8
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret87 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !320, metadata !166), !dbg !321
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !322, metadata !166), !dbg !323
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !324, metadata !166), !dbg !325
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !326, metadata !166), !dbg !327
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !328, metadata !166), !dbg !329
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !330, metadata !166), !dbg !331
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !332, metadata !166), !dbg !333
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !334, metadata !166), !dbg !335
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !336, metadata !166), !dbg !337
  call void @llvm.dbg.declare(metadata i64* %out_avail, metadata !338, metadata !166), !dbg !339
  call void @llvm.dbg.declare(metadata i64* %buf_avail, metadata !340, metadata !166), !dbg !341
  %0 = load i32, i32* %action.addr, align 4, !dbg !342
  %cmp = icmp eq i32 %0, 1, !dbg !344
  br i1 %cmp, label %if.then, label %if.end, !dbg !345

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !346
  br label %return, !dbg !346

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !347
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 7, !dbg !349
  %2 = load i64, i64* %pos, align 8, !dbg !349
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !350
  %filtered = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 8, !dbg !351
  %4 = load i64, i64* %filtered, align 8, !dbg !351
  %cmp1 = icmp ult i64 %2, %4, !dbg !352
  br i1 %cmp1, label %if.then2, label %if.end14, !dbg !353

if.then2:                                         ; preds = %if.end
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !354
  %buffer = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 10, !dbg !356
  %arraydecay = getelementptr inbounds [0 x i8], [0 x i8]* %buffer, i32 0, i32 0, !dbg !354
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !357
  %pos3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 7, !dbg !358
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !359
  %filtered4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 8, !dbg !360
  %8 = load i64, i64* %filtered4, align 8, !dbg !360
  %9 = load i8*, i8** %out.addr, align 8, !dbg !361
  %10 = load i64*, i64** %out_pos.addr, align 8, !dbg !362
  %11 = load i64, i64* %out_size.addr, align 8, !dbg !363
  %call = call i64 @lzma_bufcpy(i8* %arraydecay, i64* %pos3, i64 %8, i8* %9, i64* %10, i64 %11), !dbg !364
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !365
  %pos5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 7, !dbg !367
  %13 = load i64, i64* %pos5, align 8, !dbg !367
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !368
  %filtered6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 8, !dbg !369
  %15 = load i64, i64* %filtered6, align 8, !dbg !369
  %cmp7 = icmp ult i64 %13, %15, !dbg !370
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !371

if.then8:                                         ; preds = %if.then2
  store i32 0, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end9:                                          ; preds = %if.then2
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !373
  %end_was_reached = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 1, !dbg !375
  %17 = load i8, i8* %end_was_reached, align 8, !dbg !375
  %tobool = trunc i8 %17 to i1, !dbg !375
  br i1 %tobool, label %if.then10, label %if.end13, !dbg !376

if.then10:                                        ; preds = %if.end9
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !377
  %filtered11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 8, !dbg !377
  %19 = load i64, i64* %filtered11, align 8, !dbg !377
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !377
  %size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 9, !dbg !377
  %21 = load i64, i64* %size, align 8, !dbg !377
  %cmp12 = icmp eq i64 %19, %21, !dbg !377
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !377

cond.true:                                        ; preds = %if.then10
  br label %cond.end, !dbg !379

cond.false:                                       ; preds = %if.then10
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 96, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !381
  unreachable, !dbg !381
                                                  ; No predecessors!
  br label %cond.end, !dbg !383

cond.end:                                         ; preds = %22, %cond.true
  store i32 1, i32* %retval, align 4, !dbg !385
  br label %return, !dbg !385

if.end13:                                         ; preds = %if.end9
  br label %if.end14, !dbg !386

if.end14:                                         ; preds = %if.end13, %if.end
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !387
  %filtered15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 8, !dbg !388
  store i64 0, i64* %filtered15, align 8, !dbg !389
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !390
  %end_was_reached16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 1, !dbg !390
  %25 = load i8, i8* %end_was_reached16, align 8, !dbg !390
  %tobool17 = trunc i8 %25 to i1, !dbg !390
  br i1 %tobool17, label %cond.false19, label %cond.true18, !dbg !390

cond.true18:                                      ; preds = %if.end14
  br label %cond.end20, !dbg !391

cond.false19:                                     ; preds = %if.end14
  call void @__assert_fail(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 104, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !393
  unreachable, !dbg !393
                                                  ; No predecessors!
  br label %cond.end20, !dbg !395

cond.end20:                                       ; preds = %26, %cond.true18
  %27 = load i64, i64* %out_size.addr, align 8, !dbg !397
  %28 = load i64*, i64** %out_pos.addr, align 8, !dbg !398
  %29 = load i64, i64* %28, align 8, !dbg !399
  %sub = sub i64 %27, %29, !dbg !400
  store i64 %sub, i64* %out_avail, align 8, !dbg !401
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !402
  %size21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 9, !dbg !403
  %31 = load i64, i64* %size21, align 8, !dbg !403
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !404
  %pos22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 7, !dbg !405
  %33 = load i64, i64* %pos22, align 8, !dbg !405
  %sub23 = sub i64 %31, %33, !dbg !406
  store i64 %sub23, i64* %buf_avail, align 8, !dbg !407
  %34 = load i64, i64* %out_avail, align 8, !dbg !408
  %35 = load i64, i64* %buf_avail, align 8, !dbg !410
  %cmp24 = icmp ugt i64 %34, %35, !dbg !411
  br i1 %cmp24, label %if.then26, label %lor.lhs.false, !dbg !412

lor.lhs.false:                                    ; preds = %cond.end20
  %36 = load i64, i64* %buf_avail, align 8, !dbg !413
  %cmp25 = icmp eq i64 %36, 0, !dbg !415
  br i1 %cmp25, label %if.then26, label %if.else63, !dbg !416

if.then26:                                        ; preds = %lor.lhs.false, %cond.end20
  call void @llvm.dbg.declare(metadata i64* %size27, metadata !417, metadata !166), !dbg !419
  call void @llvm.dbg.declare(metadata i64* %filtered28, metadata !420, metadata !166), !dbg !421
  call void @llvm.dbg.declare(metadata i64* %unfiltered, metadata !422, metadata !166), !dbg !423
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !424, metadata !166), !dbg !426
  %37 = load i64*, i64** %out_pos.addr, align 8, !dbg !427
  %38 = load i64, i64* %37, align 8, !dbg !428
  store i64 %38, i64* %out_start, align 8, !dbg !426
  %39 = load i8*, i8** %out.addr, align 8, !dbg !429
  %40 = load i64*, i64** %out_pos.addr, align 8, !dbg !430
  %41 = load i64, i64* %40, align 8, !dbg !431
  %add.ptr = getelementptr inbounds i8, i8* %39, i64 %41, !dbg !432
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !433
  %buffer29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 10, !dbg !434
  %arraydecay30 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer29, i32 0, i32 0, !dbg !433
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !435
  %pos31 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 7, !dbg !436
  %44 = load i64, i64* %pos31, align 8, !dbg !436
  %add.ptr32 = getelementptr inbounds i8, i8* %arraydecay30, i64 %44, !dbg !437
  %45 = load i64, i64* %buf_avail, align 8, !dbg !438
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %add.ptr32, i64 %45, i32 1, i1 false), !dbg !439
  %46 = load i64, i64* %buf_avail, align 8, !dbg !440
  %47 = load i64*, i64** %out_pos.addr, align 8, !dbg !441
  %48 = load i64, i64* %47, align 8, !dbg !442
  %add = add i64 %48, %46, !dbg !442
  store i64 %add, i64* %47, align 8, !dbg !442
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !443, metadata !166), !dbg !446
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !447
  %50 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !448
  %51 = load i8*, i8** %in.addr, align 8, !dbg !449
  %52 = load i64*, i64** %in_pos.addr, align 8, !dbg !450
  %53 = load i64, i64* %in_size.addr, align 8, !dbg !451
  %54 = load i8*, i8** %out.addr, align 8, !dbg !452
  %55 = load i64*, i64** %out_pos.addr, align 8, !dbg !453
  %56 = load i64, i64* %out_size.addr, align 8, !dbg !454
  %57 = load i32, i32* %action.addr, align 4, !dbg !455
  %call33 = call i32 @copy_or_code(%struct.lzma_coder_s* %49, %struct.lzma_allocator* %50, i8* %51, i64* %52, i64 %53, i8* %54, i64* %55, i64 %56, i32 %57), !dbg !456
  store i32 %call33, i32* %ret, align 4, !dbg !446
  %58 = load i32, i32* %ret, align 4, !dbg !457
  %cmp34 = icmp ne i32 %58, 1, !dbg !457
  br i1 %cmp34, label %cond.true35, label %cond.false36, !dbg !457

cond.true35:                                      ; preds = %if.then26
  br label %cond.end37, !dbg !458

cond.false36:                                     ; preds = %if.then26
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 134, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !460
  unreachable, !dbg !460
                                                  ; No predecessors!
  br label %cond.end37, !dbg !462

cond.end37:                                       ; preds = %59, %cond.true35
  %60 = load i32, i32* %ret, align 4, !dbg !464
  %cmp38 = icmp ne i32 %60, 0, !dbg !466
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !467

if.then39:                                        ; preds = %cond.end37
  %61 = load i32, i32* %ret, align 4, !dbg !468
  store i32 %61, i32* %retval, align 4, !dbg !469
  br label %return, !dbg !469

if.end40:                                         ; preds = %cond.end37
  %62 = load i64*, i64** %out_pos.addr, align 8, !dbg !470
  %63 = load i64, i64* %62, align 8, !dbg !471
  %64 = load i64, i64* %out_start, align 8, !dbg !472
  %sub41 = sub i64 %63, %64, !dbg !473
  store i64 %sub41, i64* %size27, align 8, !dbg !474
  %65 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !475
  %66 = load i8*, i8** %out.addr, align 8, !dbg !476
  %67 = load i64, i64* %out_start, align 8, !dbg !477
  %add.ptr42 = getelementptr inbounds i8, i8* %66, i64 %67, !dbg !478
  %68 = load i64, i64* %size27, align 8, !dbg !479
  %call43 = call i64 @call_filter(%struct.lzma_coder_s* %65, i8* %add.ptr42, i64 %68), !dbg !480
  store i64 %call43, i64* %filtered28, align 8, !dbg !481
  %69 = load i64, i64* %size27, align 8, !dbg !482
  %70 = load i64, i64* %filtered28, align 8, !dbg !483
  %sub44 = sub i64 %69, %70, !dbg !484
  store i64 %sub44, i64* %unfiltered, align 8, !dbg !485
  %71 = load i64, i64* %unfiltered, align 8, !dbg !486
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !486
  %allocated = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 6, !dbg !486
  %73 = load i64, i64* %allocated, align 8, !dbg !486
  %div = udiv i64 %73, 2, !dbg !486
  %cmp45 = icmp ule i64 %71, %div, !dbg !486
  br i1 %cmp45, label %cond.true46, label %cond.false47, !dbg !486

cond.true46:                                      ; preds = %if.end40
  br label %cond.end48, !dbg !487

cond.false47:                                     ; preds = %if.end40
  call void @__assert_fail(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 144, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !489
  unreachable, !dbg !489
                                                  ; No predecessors!
  br label %cond.end48, !dbg !491

cond.end48:                                       ; preds = %74, %cond.true46
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !493
  %pos49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 7, !dbg !494
  store i64 0, i64* %pos49, align 8, !dbg !495
  %76 = load i64, i64* %unfiltered, align 8, !dbg !496
  %77 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !497
  %size50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %77, i32 0, i32 9, !dbg !498
  store i64 %76, i64* %size50, align 8, !dbg !499
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !500
  %end_was_reached51 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 1, !dbg !502
  %79 = load i8, i8* %end_was_reached51, align 8, !dbg !502
  %tobool52 = trunc i8 %79 to i1, !dbg !502
  br i1 %tobool52, label %if.then53, label %if.else, !dbg !503

if.then53:                                        ; preds = %cond.end48
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !504
  %size54 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 9, !dbg !506
  store i64 0, i64* %size54, align 8, !dbg !507
  br label %if.end62, !dbg !508

if.else:                                          ; preds = %cond.end48
  %81 = load i64, i64* %unfiltered, align 8, !dbg !509
  %cmp55 = icmp ugt i64 %81, 0, !dbg !512
  br i1 %cmp55, label %if.then56, label %if.end61, !dbg !509

if.then56:                                        ; preds = %if.else
  %82 = load i64, i64* %unfiltered, align 8, !dbg !513
  %83 = load i64*, i64** %out_pos.addr, align 8, !dbg !515
  %84 = load i64, i64* %83, align 8, !dbg !516
  %sub57 = sub i64 %84, %82, !dbg !516
  store i64 %sub57, i64* %83, align 8, !dbg !516
  %85 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !517
  %buffer58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %85, i32 0, i32 10, !dbg !518
  %arraydecay59 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer58, i32 0, i32 0, !dbg !519
  %86 = load i8*, i8** %out.addr, align 8, !dbg !520
  %87 = load i64*, i64** %out_pos.addr, align 8, !dbg !521
  %88 = load i64, i64* %87, align 8, !dbg !522
  %add.ptr60 = getelementptr inbounds i8, i8* %86, i64 %88, !dbg !523
  %89 = load i64, i64* %unfiltered, align 8, !dbg !524
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay59, i8* %add.ptr60, i64 %89, i32 1, i1 false), !dbg !519
  br label %if.end61, !dbg !525

if.end61:                                         ; preds = %if.then56, %if.else
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.then53
  br label %if.end78, !dbg !526

if.else63:                                        ; preds = %lor.lhs.false
  %90 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %pos64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %90, i32 0, i32 7, !dbg !530
  %91 = load i64, i64* %pos64, align 8, !dbg !530
  %cmp65 = icmp ugt i64 %91, 0, !dbg !531
  br i1 %cmp65, label %if.then66, label %if.end77, !dbg !527

if.then66:                                        ; preds = %if.else63
  %92 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !532
  %buffer67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %92, i32 0, i32 10, !dbg !534
  %arraydecay68 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer67, i32 0, i32 0, !dbg !535
  %93 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !536
  %buffer69 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %93, i32 0, i32 10, !dbg !537
  %arraydecay70 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer69, i32 0, i32 0, !dbg !536
  %94 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !538
  %pos71 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %94, i32 0, i32 7, !dbg !539
  %95 = load i64, i64* %pos71, align 8, !dbg !539
  %add.ptr72 = getelementptr inbounds i8, i8* %arraydecay70, i64 %95, !dbg !540
  %96 = load i64, i64* %buf_avail, align 8, !dbg !541
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %arraydecay68, i8* %add.ptr72, i64 %96, i32 1, i1 false), !dbg !535
  %97 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !542
  %pos73 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %97, i32 0, i32 7, !dbg !543
  %98 = load i64, i64* %pos73, align 8, !dbg !543
  %99 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !544
  %size74 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %99, i32 0, i32 9, !dbg !545
  %100 = load i64, i64* %size74, align 8, !dbg !546
  %sub75 = sub i64 %100, %98, !dbg !546
  store i64 %sub75, i64* %size74, align 8, !dbg !546
  %101 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !547
  %pos76 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %101, i32 0, i32 7, !dbg !548
  store i64 0, i64* %pos76, align 8, !dbg !549
  br label %if.end77, !dbg !550

if.end77:                                         ; preds = %if.then66, %if.else63
  br label %if.end78

if.end78:                                         ; preds = %if.end77, %if.end62
  %102 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !551
  %pos79 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %102, i32 0, i32 7, !dbg !551
  %103 = load i64, i64* %pos79, align 8, !dbg !551
  %cmp80 = icmp eq i64 %103, 0, !dbg !551
  br i1 %cmp80, label %cond.true81, label %cond.false82, !dbg !551

cond.true81:                                      ; preds = %if.end78
  br label %cond.end83, !dbg !552

cond.false82:                                     ; preds = %if.end78
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 168, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !553
  unreachable, !dbg !553
                                                  ; No predecessors!
  br label %cond.end83, !dbg !554

cond.end83:                                       ; preds = %104, %cond.true81
  %105 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !555
  %size84 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %105, i32 0, i32 9, !dbg !557
  %106 = load i64, i64* %size84, align 8, !dbg !557
  %cmp85 = icmp ugt i64 %106, 0, !dbg !558
  br i1 %cmp85, label %if.then86, label %if.end116, !dbg !559

if.then86:                                        ; preds = %cond.end83
  call void @llvm.dbg.declare(metadata i32* %ret87, metadata !560, metadata !166), !dbg !563
  %107 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !564
  %108 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !565
  %109 = load i8*, i8** %in.addr, align 8, !dbg !566
  %110 = load i64*, i64** %in_pos.addr, align 8, !dbg !567
  %111 = load i64, i64* %in_size.addr, align 8, !dbg !568
  %112 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !569
  %buffer88 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %112, i32 0, i32 10, !dbg !570
  %arraydecay89 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer88, i32 0, i32 0, !dbg !569
  %113 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !571
  %size90 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %113, i32 0, i32 9, !dbg !572
  %114 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !573
  %allocated91 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %114, i32 0, i32 6, !dbg !574
  %115 = load i64, i64* %allocated91, align 8, !dbg !574
  %116 = load i32, i32* %action.addr, align 4, !dbg !575
  %call92 = call i32 @copy_or_code(%struct.lzma_coder_s* %107, %struct.lzma_allocator* %108, i8* %109, i64* %110, i64 %111, i8* %arraydecay89, i64* %size90, i64 %115, i32 %116), !dbg !576
  store i32 %call92, i32* %ret87, align 4, !dbg !563
  %117 = load i32, i32* %ret87, align 4, !dbg !577
  %cmp93 = icmp ne i32 %117, 1, !dbg !577
  br i1 %cmp93, label %cond.true94, label %cond.false95, !dbg !577

cond.true94:                                      ; preds = %if.then86
  br label %cond.end96, !dbg !578

cond.false95:                                     ; preds = %if.then86
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 180, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.simple_code, i32 0, i32 0)) #5, !dbg !580
  unreachable, !dbg !580
                                                  ; No predecessors!
  br label %cond.end96, !dbg !582

cond.end96:                                       ; preds = %118, %cond.true94
  %119 = load i32, i32* %ret87, align 4, !dbg !584
  %cmp97 = icmp ne i32 %119, 0, !dbg !586
  br i1 %cmp97, label %if.then98, label %if.end99, !dbg !587

if.then98:                                        ; preds = %cond.end96
  %120 = load i32, i32* %ret87, align 4, !dbg !588
  store i32 %120, i32* %retval, align 4, !dbg !589
  br label %return, !dbg !589

if.end99:                                         ; preds = %cond.end96
  %121 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !590
  %122 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !591
  %buffer100 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %122, i32 0, i32 10, !dbg !592
  %arraydecay101 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer100, i32 0, i32 0, !dbg !591
  %123 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !593
  %size102 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %123, i32 0, i32 9, !dbg !594
  %124 = load i64, i64* %size102, align 8, !dbg !594
  %call103 = call i64 @call_filter(%struct.lzma_coder_s* %121, i8* %arraydecay101, i64 %124), !dbg !595
  %125 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !596
  %filtered104 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %125, i32 0, i32 8, !dbg !597
  store i64 %call103, i64* %filtered104, align 8, !dbg !598
  %126 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !599
  %end_was_reached105 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %126, i32 0, i32 1, !dbg !601
  %127 = load i8, i8* %end_was_reached105, align 8, !dbg !601
  %tobool106 = trunc i8 %127 to i1, !dbg !601
  br i1 %tobool106, label %if.then107, label %if.end110, !dbg !602

if.then107:                                       ; preds = %if.end99
  %128 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !603
  %size108 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %128, i32 0, i32 9, !dbg !604
  %129 = load i64, i64* %size108, align 8, !dbg !604
  %130 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !605
  %filtered109 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %130, i32 0, i32 8, !dbg !606
  store i64 %129, i64* %filtered109, align 8, !dbg !607
  br label %if.end110, !dbg !605

if.end110:                                        ; preds = %if.then107, %if.end99
  %131 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !608
  %buffer111 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %131, i32 0, i32 10, !dbg !609
  %arraydecay112 = getelementptr inbounds [0 x i8], [0 x i8]* %buffer111, i32 0, i32 0, !dbg !608
  %132 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !610
  %pos113 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %132, i32 0, i32 7, !dbg !611
  %133 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !612
  %filtered114 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %133, i32 0, i32 8, !dbg !613
  %134 = load i64, i64* %filtered114, align 8, !dbg !613
  %135 = load i8*, i8** %out.addr, align 8, !dbg !614
  %136 = load i64*, i64** %out_pos.addr, align 8, !dbg !615
  %137 = load i64, i64* %out_size.addr, align 8, !dbg !616
  %call115 = call i64 @lzma_bufcpy(i8* %arraydecay112, i64* %pos113, i64 %134, i8* %135, i64* %136, i64 %137), !dbg !617
  br label %if.end116, !dbg !618

if.end116:                                        ; preds = %if.end110, %cond.end83
  %138 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !619
  %end_was_reached117 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %138, i32 0, i32 1, !dbg !621
  %139 = load i8, i8* %end_was_reached117, align 8, !dbg !621
  %tobool118 = trunc i8 %139 to i1, !dbg !621
  br i1 %tobool118, label %land.lhs.true, label %if.end123, !dbg !622

land.lhs.true:                                    ; preds = %if.end116
  %140 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !623
  %pos119 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %140, i32 0, i32 7, !dbg !625
  %141 = load i64, i64* %pos119, align 8, !dbg !625
  %142 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !626
  %size120 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %142, i32 0, i32 9, !dbg !627
  %143 = load i64, i64* %size120, align 8, !dbg !627
  %cmp121 = icmp eq i64 %141, %143, !dbg !628
  br i1 %cmp121, label %if.then122, label %if.end123, !dbg !629

if.then122:                                       ; preds = %land.lhs.true
  store i32 1, i32* %retval, align 4, !dbg !630
  br label %return, !dbg !630

if.end123:                                        ; preds = %land.lhs.true, %if.end116
  store i32 0, i32* %retval, align 4, !dbg !631
  br label %return, !dbg !631

return:                                           ; preds = %if.end123, %if.then122, %if.then98, %if.then39, %cond.end, %if.then8, %if.then
  %144 = load i32, i32* %retval, align 4, !dbg !632
  ret i32 %144, !dbg !632
}

; Function Attrs: nounwind uwtable
define internal void @simple_coder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !157 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !633, metadata !166), !dbg !634
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !635, metadata !166), !dbg !636
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !637
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !638
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !639
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !640
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !641
  %simple = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 4, !dbg !642
  %3 = load %struct.lzma_simple_s*, %struct.lzma_simple_s** %simple, align 8, !dbg !642
  %4 = bitcast %struct.lzma_simple_s* %3 to i8*, !dbg !641
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !643
  call void @lzma_free(i8* %4, %struct.lzma_allocator* %5), !dbg !644
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !645
  %7 = bitcast %struct.lzma_coder_s* %6 to i8*, !dbg !645
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !646
  call void @lzma_free(i8* %7, %struct.lzma_allocator* %8), !dbg !647
  ret void, !dbg !648
}

; Function Attrs: nounwind uwtable
define internal i32 @simple_coder_update(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters_null, %struct.lzma_filter* %reversed_filters) #0 !dbg !158 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters_null.addr = alloca %struct.lzma_filter*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !649, metadata !166), !dbg !650
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !651, metadata !166), !dbg !652
  store %struct.lzma_filter* %filters_null, %struct.lzma_filter** %filters_null.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters_null.addr, metadata !653, metadata !166), !dbg !654
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !655, metadata !166), !dbg !656
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !657
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !658
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !659
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !660
  %add.ptr = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %2, i64 1, !dbg !661
  %call = call i32 @lzma_next_filter_update(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1, %struct.lzma_filter* %add.ptr), !dbg !662
  ret i32 %call, !dbg !663
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @copy_or_code(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !153 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !664, metadata !166), !dbg !665
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !666, metadata !166), !dbg !667
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !668, metadata !166), !dbg !669
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !670, metadata !166), !dbg !671
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !672, metadata !166), !dbg !673
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !674, metadata !166), !dbg !675
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !676, metadata !166), !dbg !677
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !678, metadata !166), !dbg !679
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !680, metadata !166), !dbg !681
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !682
  %end_was_reached = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !682
  %1 = load i8, i8* %end_was_reached, align 8, !dbg !682
  %tobool = trunc i8 %1 to i1, !dbg !682
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !682

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !683

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 26, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.copy_or_code, i32 0, i32 0)) #5, !dbg !685
  unreachable, !dbg !685
                                                  ; No predecessors!
  br label %cond.end, !dbg !687

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !689
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !691
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !692
  %4 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !692
  %cmp = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %4, null, !dbg !693
  br i1 %cmp, label %if.then, label %if.else, !dbg !694

if.then:                                          ; preds = %cond.end
  %5 = load i8*, i8** %in.addr, align 8, !dbg !695
  %6 = load i64*, i64** %in_pos.addr, align 8, !dbg !697
  %7 = load i64, i64* %in_size.addr, align 8, !dbg !698
  %8 = load i8*, i8** %out.addr, align 8, !dbg !699
  %9 = load i64*, i64** %out_pos.addr, align 8, !dbg !700
  %10 = load i64, i64* %out_size.addr, align 8, !dbg !701
  %call = call i64 @lzma_bufcpy(i8* %5, i64* %6, i64 %7, i8* %8, i64* %9, i64 %10), !dbg !702
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !703
  %is_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 2, !dbg !705
  %12 = load i8, i8* %is_encoder, align 1, !dbg !705
  %tobool1 = trunc i8 %12 to i1, !dbg !705
  br i1 %tobool1, label %land.lhs.true, label %if.end, !dbg !706

land.lhs.true:                                    ; preds = %if.then
  %13 = load i32, i32* %action.addr, align 4, !dbg !707
  %cmp2 = icmp eq i32 %13, 3, !dbg !709
  br i1 %cmp2, label %land.lhs.true3, label %if.end, !dbg !710

land.lhs.true3:                                   ; preds = %land.lhs.true
  %14 = load i64*, i64** %in_pos.addr, align 8, !dbg !711
  %15 = load i64, i64* %14, align 8, !dbg !712
  %16 = load i64, i64* %in_size.addr, align 8, !dbg !713
  %cmp4 = icmp eq i64 %15, %16, !dbg !714
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !715

if.then5:                                         ; preds = %land.lhs.true3
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !717
  %end_was_reached6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 1, !dbg !718
  store i8 1, i8* %end_was_reached6, align 8, !dbg !719
  br label %if.end, !dbg !717

if.end:                                           ; preds = %if.then5, %land.lhs.true3, %land.lhs.true, %if.then
  br label %if.end26, !dbg !720

if.else:                                          ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !721, metadata !166), !dbg !723
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !724
  %next7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 0, !dbg !725
  %code8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next7, i32 0, i32 3, !dbg !726
  %19 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code8, align 8, !dbg !726
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !727
  %next9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 0, !dbg !728
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next9, i32 0, i32 0, !dbg !729
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !729
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !730
  %23 = load i8*, i8** %in.addr, align 8, !dbg !731
  %24 = load i64*, i64** %in_pos.addr, align 8, !dbg !732
  %25 = load i64, i64* %in_size.addr, align 8, !dbg !733
  %26 = load i8*, i8** %out.addr, align 8, !dbg !734
  %27 = load i64*, i64** %out_pos.addr, align 8, !dbg !735
  %28 = load i64, i64* %out_size.addr, align 8, !dbg !736
  %29 = load i32, i32* %action.addr, align 4, !dbg !737
  %call11 = call i32 %19(%struct.lzma_coder_s* %21, %struct.lzma_allocator* %22, i8* %23, i64* %24, i64 %25, i8* %26, i64* %27, i64 %28, i32 %29), !dbg !724
  store i32 %call11, i32* %ret, align 4, !dbg !723
  %30 = load i32, i32* %ret, align 4, !dbg !738
  %cmp12 = icmp eq i32 %30, 1, !dbg !740
  br i1 %cmp12, label %if.then13, label %if.else21, !dbg !741

if.then13:                                        ; preds = %if.else
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !742
  %is_encoder14 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 2, !dbg !742
  %32 = load i8, i8* %is_encoder14, align 1, !dbg !742
  %tobool15 = trunc i8 %32 to i1, !dbg !742
  br i1 %tobool15, label %lor.lhs.false, label %cond.true17, !dbg !742

lor.lhs.false:                                    ; preds = %if.then13
  %33 = load i32, i32* %action.addr, align 4, !dbg !744
  %cmp16 = icmp eq i32 %33, 3, !dbg !744
  br i1 %cmp16, label %cond.true17, label %cond.false18, !dbg !744

cond.true17:                                      ; preds = %lor.lhs.false, %if.then13
  br label %cond.end19, !dbg !746

cond.false18:                                     ; preds = %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 45, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.copy_or_code, i32 0, i32 0)) #5, !dbg !748
  unreachable, !dbg !748
                                                  ; No predecessors!
  br label %cond.end19, !dbg !750

cond.end19:                                       ; preds = %34, %cond.true17
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !752
  %end_was_reached20 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 1, !dbg !753
  store i8 1, i8* %end_was_reached20, align 8, !dbg !754
  br label %if.end25, !dbg !755

if.else21:                                        ; preds = %if.else
  %36 = load i32, i32* %ret, align 4, !dbg !756
  %cmp22 = icmp ne i32 %36, 0, !dbg !759
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !756

if.then23:                                        ; preds = %if.else21
  %37 = load i32, i32* %ret, align 4, !dbg !760
  store i32 %37, i32* %retval, align 4, !dbg !762
  br label %return, !dbg !762

if.end24:                                         ; preds = %if.else21
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %cond.end19
  br label %if.end26

if.end26:                                         ; preds = %if.end25, %if.end
  store i32 0, i32* %retval, align 4, !dbg !763
  br label %return, !dbg !763

return:                                           ; preds = %if.end26, %if.then23
  %38 = load i32, i32* %retval, align 4, !dbg !764
  ret i32 %38, !dbg !764
}

; Function Attrs: nounwind uwtable
define internal i64 @call_filter(%struct.lzma_coder_s* %coder, i8* %buffer, i64 %size) #0 !dbg !154 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %filtered = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !765, metadata !166), !dbg !766
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !767, metadata !166), !dbg !768
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !769, metadata !166), !dbg !770
  call void @llvm.dbg.declare(metadata i64* %filtered, metadata !771, metadata !166), !dbg !772
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !773
  %filter = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 3, !dbg !774
  %1 = load i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)** %filter, align 8, !dbg !774
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !775
  %simple = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 4, !dbg !776
  %3 = load %struct.lzma_simple_s*, %struct.lzma_simple_s** %simple, align 8, !dbg !776
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !777
  %now_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 5, !dbg !778
  %5 = load i32, i32* %now_pos, align 8, !dbg !778
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !779
  %is_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 2, !dbg !780
  %7 = load i8, i8* %is_encoder, align 1, !dbg !780
  %tobool = trunc i8 %7 to i1, !dbg !780
  %8 = load i8*, i8** %buffer.addr, align 8, !dbg !781
  %9 = load i64, i64* %size.addr, align 8, !dbg !782
  %call = call i64 %1(%struct.lzma_simple_s* %3, i32 %5, i1 zeroext %tobool, i8* %8, i64 %9), !dbg !773
  store i64 %call, i64* %filtered, align 8, !dbg !772
  %10 = load i64, i64* %filtered, align 8, !dbg !783
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !784
  %now_pos1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 5, !dbg !785
  %12 = load i32, i32* %now_pos1, align 8, !dbg !786
  %conv = zext i32 %12 to i64, !dbg !786
  %add = add i64 %conv, %10, !dbg !786
  %conv2 = trunc i64 %add to i32, !dbg !786
  store i32 %conv2, i32* %now_pos1, align 8, !dbg !786
  %13 = load i64, i64* %filtered, align 8, !dbg !787
  ret i64 %13, !dbg !788
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

declare i32 @lzma_next_filter_update(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!162, !163}
!llvm.ident = !{!164}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !33, globals: !159)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_coder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!33 = !{!34, !152, !153, !154, !157, !158}
!34 = distinct !DISubprogram(name: "lzma_simple_coder_init", scope: !1, file: !1, line: 228, type: !35, isLocal: false, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !90, !139, !54, !57, !57, !63, !51}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !40, line: 75, baseType: !41)
!40 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !40, line: 119, size: 512, align: 64, elements: !42)
!42 = !{!43, !79, !83, !85, !110, !115, !122, !127}
!43 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !41, file: !40, line: 121, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !40, line: 73, baseType: !46)
!46 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !47, line: 21, size: 1024, align: 64, elements: !48)
!47 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!48 = !{!49, !50, !52, !53, !69, !70, !71, !72, !73, !74, !75}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !46, file: !47, line: 23, baseType: !39, size: 512, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "end_was_reached", scope: !46, file: !47, line: 26, baseType: !51, size: 8, align: 8, offset: 512)
!51 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "is_encoder", scope: !46, file: !47, line: 32, baseType: !51, size: 8, align: 8, offset: 520)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !46, file: !47, line: 36, baseType: !54, size: 64, align: 64, offset: 576)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!57, !60, !63, !51, !66, !57}
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !58, line: 62, baseType: !59)
!58 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!59 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_simple", file: !47, line: 19, baseType: !62)
!62 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_simple_s", file: !47, line: 19, flags: DIFlagFwdDecl)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !64, line: 51, baseType: !65)
!64 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!65 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !64, line: 48, baseType: !68)
!68 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "simple", scope: !46, file: !47, line: 41, baseType: !60, size: 64, align: 64, offset: 640)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "now_pos", scope: !46, file: !47, line: 46, baseType: !63, size: 32, align: 32, offset: 704)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "allocated", scope: !46, file: !47, line: 49, baseType: !57, size: 64, align: 64, offset: 768)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !46, file: !47, line: 53, baseType: !57, size: 64, align: 64, offset: 832)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "filtered", scope: !46, file: !47, line: 57, baseType: !57, size: 64, align: 64, offset: 896)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !46, file: !47, line: 61, baseType: !57, size: 64, align: 64, offset: 960)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !46, file: !47, line: 64, baseType: !76, offset: 1024)
!76 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, align: 8, elements: !77)
!77 = !{!78}
!78 = !DISubrange(count: -1)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !41, file: !40, line: 125, baseType: !80, size: 64, align: 64, offset: 64)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !81, line: 63, baseType: !82)
!81 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !64, line: 55, baseType: !59)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !41, file: !40, line: 131, baseType: !84, size: 64, align: 64, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !64, line: 122, baseType: !59)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !41, file: !40, line: 134, baseType: !86, size: 64, align: 64, offset: 192)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !40, line: 89, baseType: !87)
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!88 = !DISubroutineType(types: !89)
!89 = !{!37, !44, !90, !103, !106, !57, !108, !106, !57, !109}
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !92)
!92 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !93)
!93 = !{!94, !98, !102}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !92, file: !4, line: 376, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DISubroutineType(types: !97)
!97 = !{!32, !32, !57, !57}
!98 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !92, file: !4, line: 390, baseType: !99, size: 64, align: 64, offset: 64)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DISubroutineType(types: !101)
!101 = !{null, !32, !32}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !92, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !104)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !67)
!106 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !107)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !66)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !41, file: !40, line: 139, baseType: !111, size: 64, align: 64, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !40, line: 97, baseType: !112)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{null, !44, !90}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !41, file: !40, line: 143, baseType: !116, size: 64, align: 64, offset: 320)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !120}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !41, file: !40, line: 147, baseType: !123, size: 64, align: 64, offset: 384)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{!37, !44, !126, !126, !82}
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !41, file: !40, line: 152, baseType: !128, size: 64, align: 64, offset: 448)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DISubroutineType(types: !130)
!130 = !{!37, !44, !90, !131, !131}
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !133)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !134, line: 65, baseType: !135)
!134 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!135 = !DICompositeType(tag: DW_TAG_structure_type, file: !134, line: 43, size: 128, align: 64, elements: !136)
!136 = !{!137, !138}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !135, file: !134, line: 54, baseType: !80, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !135, file: !134, line: 63, baseType: !32, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !141)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !40, line: 77, baseType: !142)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !40, line: 104, size: 192, align: 64, elements: !143)
!143 = !{!144, !145, !150}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !142, file: !40, line: 107, baseType: !80, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !142, file: !40, line: 111, baseType: !146, size: 64, align: 64, offset: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !40, line: 81, baseType: !147)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DISubroutineType(types: !149)
!149 = !{!37, !38, !90, !139}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !142, file: !40, line: 114, baseType: !32, size: 64, align: 64, offset: 128)
!151 = !{}
!152 = distinct !DISubprogram(name: "simple_code", scope: !1, file: !1, line: 69, type: !88, isLocal: true, isDefinition: true, scopeLine: 73, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!153 = distinct !DISubprogram(name: "copy_or_code", scope: !1, file: !1, line: 21, type: !88, isLocal: true, isDefinition: true, scopeLine: 25, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!154 = distinct !DISubprogram(name: "call_filter", scope: !1, file: !1, line: 58, type: !155, isLocal: true, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!155 = !DISubroutineType(types: !156)
!156 = !{!57, !44, !66, !57}
!157 = distinct !DISubprogram(name: "simple_coder_end", scope: !1, file: !1, line: 207, type: !113, isLocal: true, isDefinition: true, scopeLine: 208, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!158 = distinct !DISubprogram(name: "simple_coder_update", scope: !1, file: !1, line: 217, type: !129, isLocal: true, isDefinition: true, scopeLine: 220, flags: DIFlagPrototyped, isOptimized: false, variables: !151)
!159 = !{!160}
!160 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !40, line: 159, type: !161, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!161 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !39)
!162 = !{i32 2, !"Dwarf Version", i32 4}
!163 = !{i32 2, !"Debug Info Version", i32 3}
!164 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!165 = !DILocalVariable(name: "next", arg: 1, scope: !34, file: !1, line: 228, type: !38)
!166 = !DIExpression()
!167 = !DILocation(line: 228, column: 41, scope: !34)
!168 = !DILocalVariable(name: "allocator", arg: 2, scope: !34, file: !1, line: 228, type: !90)
!169 = !DILocation(line: 228, column: 63, scope: !34)
!170 = !DILocalVariable(name: "filters", arg: 3, scope: !34, file: !1, line: 229, type: !139)
!171 = !DILocation(line: 229, column: 27, scope: !34)
!172 = !DILocalVariable(name: "filter", arg: 4, scope: !34, file: !1, line: 230, type: !54)
!173 = !DILocation(line: 230, column: 12, scope: !34)
!174 = !DILocalVariable(name: "simple_size", arg: 5, scope: !34, file: !1, line: 232, type: !57)
!175 = !DILocation(line: 232, column: 10, scope: !34)
!176 = !DILocalVariable(name: "unfiltered_max", arg: 6, scope: !34, file: !1, line: 232, type: !57)
!177 = !DILocation(line: 232, column: 30, scope: !34)
!178 = !DILocalVariable(name: "alignment", arg: 7, scope: !34, file: !1, line: 233, type: !63)
!179 = !DILocation(line: 233, column: 12, scope: !34)
!180 = !DILocalVariable(name: "is_encoder", arg: 8, scope: !34, file: !1, line: 233, type: !51)
!181 = !DILocation(line: 233, column: 28, scope: !34)
!182 = !DILocation(line: 236, column: 6, scope: !183)
!183 = distinct !DILexicalBlock(scope: !34, file: !1, line: 236, column: 6)
!184 = !DILocation(line: 236, column: 12, scope: !183)
!185 = !DILocation(line: 236, column: 18, scope: !183)
!186 = !DILocation(line: 236, column: 6, scope: !34)
!187 = !DILocation(line: 242, column: 11, scope: !188)
!188 = distinct !DILexicalBlock(scope: !183, file: !1, line: 236, column: 27)
!189 = !DILocation(line: 242, column: 9, scope: !188)
!190 = !DILocation(line: 242, column: 5, scope: !188)
!191 = !DILocation(line: 242, column: 27, scope: !188)
!192 = !DILocation(line: 241, column: 17, scope: !188)
!193 = !DILocation(line: 241, column: 3, scope: !188)
!194 = !DILocation(line: 241, column: 9, scope: !188)
!195 = !DILocation(line: 241, column: 15, scope: !188)
!196 = !DILocation(line: 243, column: 7, scope: !197)
!197 = distinct !DILexicalBlock(scope: !188, file: !1, line: 243, column: 7)
!198 = !DILocation(line: 243, column: 13, scope: !197)
!199 = !DILocation(line: 243, column: 19, scope: !197)
!200 = !DILocation(line: 243, column: 7, scope: !188)
!201 = !DILocation(line: 244, column: 4, scope: !197)
!202 = !DILocation(line: 246, column: 3, scope: !188)
!203 = !DILocation(line: 246, column: 9, scope: !188)
!204 = !DILocation(line: 246, column: 14, scope: !188)
!205 = !DILocation(line: 247, column: 3, scope: !188)
!206 = !DILocation(line: 247, column: 9, scope: !188)
!207 = !DILocation(line: 247, column: 13, scope: !188)
!208 = !DILocation(line: 248, column: 3, scope: !188)
!209 = !DILocation(line: 248, column: 9, scope: !188)
!210 = !DILocation(line: 248, column: 16, scope: !188)
!211 = !DILocation(line: 250, column: 3, scope: !188)
!212 = !DILocation(line: 250, column: 9, scope: !188)
!213 = !DILocation(line: 250, column: 16, scope: !188)
!214 = !DILocation(line: 250, column: 23, scope: !188)
!215 = !DILocation(line: 251, column: 25, scope: !188)
!216 = !DILocation(line: 251, column: 3, scope: !188)
!217 = !DILocation(line: 251, column: 9, scope: !188)
!218 = !DILocation(line: 251, column: 16, scope: !188)
!219 = !DILocation(line: 251, column: 23, scope: !188)
!220 = !DILocation(line: 252, column: 32, scope: !188)
!221 = !DILocation(line: 252, column: 30, scope: !188)
!222 = !DILocation(line: 252, column: 3, scope: !188)
!223 = !DILocation(line: 252, column: 9, scope: !188)
!224 = !DILocation(line: 252, column: 16, scope: !188)
!225 = !DILocation(line: 252, column: 26, scope: !188)
!226 = !DILocation(line: 255, column: 7, scope: !227)
!227 = distinct !DILexicalBlock(scope: !188, file: !1, line: 255, column: 7)
!228 = !DILocation(line: 255, column: 19, scope: !227)
!229 = !DILocation(line: 255, column: 7, scope: !188)
!230 = !DILocation(line: 257, column: 6, scope: !231)
!231 = distinct !DILexicalBlock(scope: !227, file: !1, line: 255, column: 24)
!232 = !DILocation(line: 257, column: 19, scope: !231)
!233 = !DILocation(line: 256, column: 26, scope: !231)
!234 = !DILocation(line: 256, column: 4, scope: !231)
!235 = !DILocation(line: 256, column: 10, scope: !231)
!236 = !DILocation(line: 256, column: 17, scope: !231)
!237 = !DILocation(line: 256, column: 24, scope: !231)
!238 = !DILocation(line: 258, column: 8, scope: !239)
!239 = distinct !DILexicalBlock(scope: !231, file: !1, line: 258, column: 8)
!240 = !DILocation(line: 258, column: 14, scope: !239)
!241 = !DILocation(line: 258, column: 21, scope: !239)
!242 = !DILocation(line: 258, column: 28, scope: !239)
!243 = !DILocation(line: 258, column: 8, scope: !231)
!244 = !DILocation(line: 259, column: 5, scope: !239)
!245 = !DILocation(line: 260, column: 3, scope: !231)
!246 = !DILocation(line: 261, column: 4, scope: !247)
!247 = distinct !DILexicalBlock(scope: !227, file: !1, line: 260, column: 10)
!248 = !DILocation(line: 261, column: 10, scope: !247)
!249 = !DILocation(line: 261, column: 17, scope: !247)
!250 = !DILocation(line: 261, column: 24, scope: !247)
!251 = !DILocation(line: 263, column: 2, scope: !188)
!252 = !DILocation(line: 265, column: 6, scope: !253)
!253 = distinct !DILexicalBlock(scope: !34, file: !1, line: 265, column: 6)
!254 = !DILocation(line: 265, column: 17, scope: !253)
!255 = !DILocation(line: 265, column: 25, scope: !253)
!256 = !DILocation(line: 265, column: 6, scope: !34)
!257 = !DILocalVariable(name: "simple", scope: !258, file: !1, line: 266, type: !259)
!258 = distinct !DILexicalBlock(scope: !253, file: !1, line: 265, column: 34)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !260, size: 64, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !261)
!261 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_bcj", file: !262, line: 90, baseType: !263)
!262 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/bcj.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!263 = !DICompositeType(tag: DW_TAG_structure_type, file: !262, line: 73, size: 32, align: 32, elements: !264)
!264 = !{!265}
!265 = !DIDerivedType(tag: DW_TAG_member, name: "start_offset", scope: !263, file: !262, line: 88, baseType: !63, size: 32, align: 32)
!266 = !DILocation(line: 266, column: 27, scope: !258)
!267 = !DILocation(line: 266, column: 36, scope: !258)
!268 = !DILocation(line: 266, column: 47, scope: !258)
!269 = !DILocation(line: 267, column: 26, scope: !258)
!270 = !DILocation(line: 267, column: 34, scope: !258)
!271 = !DILocation(line: 267, column: 3, scope: !258)
!272 = !DILocation(line: 267, column: 9, scope: !258)
!273 = !DILocation(line: 267, column: 16, scope: !258)
!274 = !DILocation(line: 267, column: 24, scope: !258)
!275 = !DILocation(line: 268, column: 7, scope: !276)
!276 = distinct !DILexicalBlock(scope: !258, file: !1, line: 268, column: 7)
!277 = !DILocation(line: 268, column: 13, scope: !276)
!278 = !DILocation(line: 268, column: 20, scope: !276)
!279 = !DILocation(line: 268, column: 31, scope: !276)
!280 = !DILocation(line: 268, column: 41, scope: !276)
!281 = !DILocation(line: 268, column: 28, scope: !276)
!282 = !DILocation(line: 268, column: 7, scope: !258)
!283 = !DILocation(line: 269, column: 4, scope: !276)
!284 = !DILocation(line: 270, column: 2, scope: !258)
!285 = !DILocation(line: 271, column: 3, scope: !286)
!286 = distinct !DILexicalBlock(scope: !253, file: !1, line: 270, column: 9)
!287 = !DILocation(line: 271, column: 9, scope: !286)
!288 = !DILocation(line: 271, column: 16, scope: !286)
!289 = !DILocation(line: 271, column: 24, scope: !286)
!290 = !DILocation(line: 275, column: 28, scope: !34)
!291 = !DILocation(line: 275, column: 2, scope: !34)
!292 = !DILocation(line: 275, column: 8, scope: !34)
!293 = !DILocation(line: 275, column: 15, scope: !34)
!294 = !DILocation(line: 275, column: 26, scope: !34)
!295 = !DILocation(line: 276, column: 2, scope: !34)
!296 = !DILocation(line: 276, column: 8, scope: !34)
!297 = !DILocation(line: 276, column: 15, scope: !34)
!298 = !DILocation(line: 276, column: 31, scope: !34)
!299 = !DILocation(line: 277, column: 2, scope: !34)
!300 = !DILocation(line: 277, column: 8, scope: !34)
!301 = !DILocation(line: 277, column: 15, scope: !34)
!302 = !DILocation(line: 277, column: 19, scope: !34)
!303 = !DILocation(line: 278, column: 2, scope: !34)
!304 = !DILocation(line: 278, column: 8, scope: !34)
!305 = !DILocation(line: 278, column: 15, scope: !34)
!306 = !DILocation(line: 278, column: 24, scope: !34)
!307 = !DILocation(line: 279, column: 2, scope: !34)
!308 = !DILocation(line: 279, column: 8, scope: !34)
!309 = !DILocation(line: 279, column: 15, scope: !34)
!310 = !DILocation(line: 279, column: 20, scope: !34)
!311 = !DILocation(line: 282, column: 5, scope: !34)
!312 = !DILocation(line: 282, column: 11, scope: !34)
!313 = !DILocation(line: 282, column: 18, scope: !34)
!314 = !DILocation(line: 282, column: 24, scope: !34)
!315 = !DILocation(line: 282, column: 35, scope: !34)
!316 = !DILocation(line: 282, column: 43, scope: !34)
!317 = !DILocation(line: 281, column: 9, scope: !34)
!318 = !DILocation(line: 281, column: 2, scope: !34)
!319 = !DILocation(line: 283, column: 1, scope: !34)
!320 = !DILocalVariable(name: "coder", arg: 1, scope: !152, file: !1, line: 69, type: !44)
!321 = !DILocation(line: 69, column: 25, scope: !152)
!322 = !DILocalVariable(name: "allocator", arg: 2, scope: !152, file: !1, line: 69, type: !90)
!323 = !DILocation(line: 69, column: 48, scope: !152)
!324 = !DILocalVariable(name: "in", arg: 3, scope: !152, file: !1, line: 70, type: !103)
!325 = !DILocation(line: 70, column: 32, scope: !152)
!326 = !DILocalVariable(name: "in_pos", arg: 4, scope: !152, file: !1, line: 70, type: !106)
!327 = !DILocation(line: 70, column: 58, scope: !152)
!328 = !DILocalVariable(name: "in_size", arg: 5, scope: !152, file: !1, line: 71, type: !57)
!329 = !DILocation(line: 71, column: 10, scope: !152)
!330 = !DILocalVariable(name: "out", arg: 6, scope: !152, file: !1, line: 71, type: !108)
!331 = !DILocation(line: 71, column: 42, scope: !152)
!332 = !DILocalVariable(name: "out_pos", arg: 7, scope: !152, file: !1, line: 72, type: !106)
!333 = !DILocation(line: 72, column: 25, scope: !152)
!334 = !DILocalVariable(name: "out_size", arg: 8, scope: !152, file: !1, line: 72, type: !57)
!335 = !DILocation(line: 72, column: 41, scope: !152)
!336 = !DILocalVariable(name: "action", arg: 9, scope: !152, file: !1, line: 72, type: !109)
!337 = !DILocation(line: 72, column: 63, scope: !152)
!338 = !DILocalVariable(name: "out_avail", scope: !152, file: !1, line: 74, type: !57)
!339 = !DILocation(line: 74, column: 9, scope: !152)
!340 = !DILocalVariable(name: "buf_avail", scope: !152, file: !1, line: 75, type: !57)
!341 = !DILocation(line: 75, column: 9, scope: !152)
!342 = !DILocation(line: 82, column: 6, scope: !343)
!343 = distinct !DILexicalBlock(scope: !152, file: !1, line: 82, column: 6)
!344 = !DILocation(line: 82, column: 13, scope: !343)
!345 = !DILocation(line: 82, column: 6, scope: !152)
!346 = !DILocation(line: 83, column: 3, scope: !343)
!347 = !DILocation(line: 86, column: 6, scope: !348)
!348 = distinct !DILexicalBlock(scope: !152, file: !1, line: 86, column: 6)
!349 = !DILocation(line: 86, column: 13, scope: !348)
!350 = !DILocation(line: 86, column: 19, scope: !348)
!351 = !DILocation(line: 86, column: 26, scope: !348)
!352 = !DILocation(line: 86, column: 17, scope: !348)
!353 = !DILocation(line: 86, column: 6, scope: !152)
!354 = !DILocation(line: 87, column: 15, scope: !355)
!355 = distinct !DILexicalBlock(scope: !348, file: !1, line: 86, column: 36)
!356 = !DILocation(line: 87, column: 22, scope: !355)
!357 = !DILocation(line: 87, column: 31, scope: !355)
!358 = !DILocation(line: 87, column: 38, scope: !355)
!359 = !DILocation(line: 87, column: 43, scope: !355)
!360 = !DILocation(line: 87, column: 50, scope: !355)
!361 = !DILocation(line: 88, column: 5, scope: !355)
!362 = !DILocation(line: 88, column: 10, scope: !355)
!363 = !DILocation(line: 88, column: 19, scope: !355)
!364 = !DILocation(line: 87, column: 3, scope: !355)
!365 = !DILocation(line: 92, column: 7, scope: !366)
!366 = distinct !DILexicalBlock(scope: !355, file: !1, line: 92, column: 7)
!367 = !DILocation(line: 92, column: 14, scope: !366)
!368 = !DILocation(line: 92, column: 20, scope: !366)
!369 = !DILocation(line: 92, column: 27, scope: !366)
!370 = !DILocation(line: 92, column: 18, scope: !366)
!371 = !DILocation(line: 92, column: 7, scope: !355)
!372 = !DILocation(line: 93, column: 4, scope: !366)
!373 = !DILocation(line: 95, column: 7, scope: !374)
!374 = distinct !DILexicalBlock(scope: !355, file: !1, line: 95, column: 7)
!375 = !DILocation(line: 95, column: 14, scope: !374)
!376 = !DILocation(line: 95, column: 7, scope: !355)
!377 = !DILocation(line: 96, column: 4, scope: !378)
!378 = distinct !DILexicalBlock(scope: !374, file: !1, line: 95, column: 31)
!379 = !DILocation(line: 96, column: 4, scope: !380)
!380 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!381 = !DILocation(line: 96, column: 4, scope: !382)
!382 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 2)
!383 = !DILocation(line: 96, column: 4, scope: !384)
!384 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 3)
!385 = !DILocation(line: 97, column: 4, scope: !378)
!386 = !DILocation(line: 99, column: 2, scope: !355)
!387 = !DILocation(line: 102, column: 2, scope: !152)
!388 = !DILocation(line: 102, column: 9, scope: !152)
!389 = !DILocation(line: 102, column: 18, scope: !152)
!390 = !DILocation(line: 104, column: 2, scope: !152)
!391 = !DILocation(line: 104, column: 2, scope: !392)
!392 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 1)
!393 = !DILocation(line: 104, column: 2, scope: !394)
!394 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 2)
!395 = !DILocation(line: 104, column: 2, scope: !396)
!396 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 3)
!397 = !DILocation(line: 111, column: 14, scope: !152)
!398 = !DILocation(line: 111, column: 26, scope: !152)
!399 = !DILocation(line: 111, column: 25, scope: !152)
!400 = !DILocation(line: 111, column: 23, scope: !152)
!401 = !DILocation(line: 111, column: 12, scope: !152)
!402 = !DILocation(line: 112, column: 14, scope: !152)
!403 = !DILocation(line: 112, column: 21, scope: !152)
!404 = !DILocation(line: 112, column: 28, scope: !152)
!405 = !DILocation(line: 112, column: 35, scope: !152)
!406 = !DILocation(line: 112, column: 26, scope: !152)
!407 = !DILocation(line: 112, column: 12, scope: !152)
!408 = !DILocation(line: 113, column: 6, scope: !409)
!409 = distinct !DILexicalBlock(scope: !152, file: !1, line: 113, column: 6)
!410 = !DILocation(line: 113, column: 18, scope: !409)
!411 = !DILocation(line: 113, column: 16, scope: !409)
!412 = !DILocation(line: 113, column: 28, scope: !409)
!413 = !DILocation(line: 113, column: 31, scope: !414)
!414 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 1)
!415 = !DILocation(line: 113, column: 41, scope: !414)
!416 = !DILocation(line: 113, column: 6, scope: !414)
!417 = !DILocalVariable(name: "size", scope: !418, file: !1, line: 114, type: !57)
!418 = distinct !DILexicalBlock(scope: !409, file: !1, line: 113, column: 47)
!419 = !DILocation(line: 114, column: 10, scope: !418)
!420 = !DILocalVariable(name: "filtered", scope: !418, file: !1, line: 115, type: !57)
!421 = !DILocation(line: 115, column: 10, scope: !418)
!422 = !DILocalVariable(name: "unfiltered", scope: !418, file: !1, line: 116, type: !57)
!423 = !DILocation(line: 116, column: 10, scope: !418)
!424 = !DILocalVariable(name: "out_start", scope: !418, file: !1, line: 120, type: !425)
!425 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !57)
!426 = !DILocation(line: 120, column: 16, scope: !418)
!427 = !DILocation(line: 120, column: 29, scope: !418)
!428 = !DILocation(line: 120, column: 28, scope: !418)
!429 = !DILocation(line: 126, column: 10, scope: !418)
!430 = !DILocation(line: 126, column: 17, scope: !418)
!431 = !DILocation(line: 126, column: 16, scope: !418)
!432 = !DILocation(line: 126, column: 14, scope: !418)
!433 = !DILocation(line: 126, column: 26, scope: !418)
!434 = !DILocation(line: 126, column: 33, scope: !418)
!435 = !DILocation(line: 126, column: 42, scope: !418)
!436 = !DILocation(line: 126, column: 49, scope: !418)
!437 = !DILocation(line: 126, column: 40, scope: !418)
!438 = !DILocation(line: 126, column: 54, scope: !418)
!439 = !DILocation(line: 126, column: 3, scope: !418)
!440 = !DILocation(line: 127, column: 15, scope: !418)
!441 = !DILocation(line: 127, column: 4, scope: !418)
!442 = !DILocation(line: 127, column: 12, scope: !418)
!443 = !DILocalVariable(name: "ret", scope: !444, file: !1, line: 131, type: !445)
!444 = distinct !DILexicalBlock(scope: !418, file: !1, line: 130, column: 3)
!445 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!446 = !DILocation(line: 131, column: 19, scope: !444)
!447 = !DILocation(line: 131, column: 38, scope: !444)
!448 = !DILocation(line: 131, column: 45, scope: !444)
!449 = !DILocation(line: 132, column: 6, scope: !444)
!450 = !DILocation(line: 132, column: 10, scope: !444)
!451 = !DILocation(line: 132, column: 18, scope: !444)
!452 = !DILocation(line: 133, column: 6, scope: !444)
!453 = !DILocation(line: 133, column: 11, scope: !444)
!454 = !DILocation(line: 133, column: 20, scope: !444)
!455 = !DILocation(line: 133, column: 30, scope: !444)
!456 = !DILocation(line: 131, column: 25, scope: !444)
!457 = !DILocation(line: 134, column: 4, scope: !444)
!458 = !DILocation(line: 134, column: 4, scope: !459)
!459 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 1)
!460 = !DILocation(line: 134, column: 4, scope: !461)
!461 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 2)
!462 = !DILocation(line: 134, column: 4, scope: !463)
!463 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 3)
!464 = !DILocation(line: 135, column: 8, scope: !465)
!465 = distinct !DILexicalBlock(scope: !444, file: !1, line: 135, column: 8)
!466 = !DILocation(line: 135, column: 12, scope: !465)
!467 = !DILocation(line: 135, column: 8, scope: !444)
!468 = !DILocation(line: 136, column: 12, scope: !465)
!469 = !DILocation(line: 136, column: 5, scope: !465)
!470 = !DILocation(line: 140, column: 11, scope: !418)
!471 = !DILocation(line: 140, column: 10, scope: !418)
!472 = !DILocation(line: 140, column: 21, scope: !418)
!473 = !DILocation(line: 140, column: 19, scope: !418)
!474 = !DILocation(line: 140, column: 8, scope: !418)
!475 = !DILocation(line: 141, column: 26, scope: !418)
!476 = !DILocation(line: 141, column: 33, scope: !418)
!477 = !DILocation(line: 141, column: 39, scope: !418)
!478 = !DILocation(line: 141, column: 37, scope: !418)
!479 = !DILocation(line: 141, column: 50, scope: !418)
!480 = !DILocation(line: 141, column: 14, scope: !418)
!481 = !DILocation(line: 141, column: 12, scope: !418)
!482 = !DILocation(line: 143, column: 16, scope: !418)
!483 = !DILocation(line: 143, column: 23, scope: !418)
!484 = !DILocation(line: 143, column: 21, scope: !418)
!485 = !DILocation(line: 143, column: 14, scope: !418)
!486 = !DILocation(line: 144, column: 3, scope: !418)
!487 = !DILocation(line: 144, column: 3, scope: !488)
!488 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 1)
!489 = !DILocation(line: 144, column: 3, scope: !490)
!490 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 2)
!491 = !DILocation(line: 144, column: 3, scope: !492)
!492 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 3)
!493 = !DILocation(line: 148, column: 3, scope: !418)
!494 = !DILocation(line: 148, column: 10, scope: !418)
!495 = !DILocation(line: 148, column: 14, scope: !418)
!496 = !DILocation(line: 149, column: 17, scope: !418)
!497 = !DILocation(line: 149, column: 3, scope: !418)
!498 = !DILocation(line: 149, column: 10, scope: !418)
!499 = !DILocation(line: 149, column: 15, scope: !418)
!500 = !DILocation(line: 151, column: 7, scope: !501)
!501 = distinct !DILexicalBlock(scope: !418, file: !1, line: 151, column: 7)
!502 = !DILocation(line: 151, column: 14, scope: !501)
!503 = !DILocation(line: 151, column: 7, scope: !418)
!504 = !DILocation(line: 154, column: 4, scope: !505)
!505 = distinct !DILexicalBlock(scope: !501, file: !1, line: 151, column: 31)
!506 = !DILocation(line: 154, column: 11, scope: !505)
!507 = !DILocation(line: 154, column: 16, scope: !505)
!508 = !DILocation(line: 156, column: 3, scope: !505)
!509 = !DILocation(line: 156, column: 14, scope: !510)
!510 = !DILexicalBlockFile(scope: !511, file: !1, discriminator: 1)
!511 = distinct !DILexicalBlock(scope: !501, file: !1, line: 156, column: 14)
!512 = !DILocation(line: 156, column: 25, scope: !510)
!513 = !DILocation(line: 159, column: 16, scope: !514)
!514 = distinct !DILexicalBlock(scope: !511, file: !1, line: 156, column: 30)
!515 = !DILocation(line: 159, column: 5, scope: !514)
!516 = !DILocation(line: 159, column: 13, scope: !514)
!517 = !DILocation(line: 160, column: 11, scope: !514)
!518 = !DILocation(line: 160, column: 18, scope: !514)
!519 = !DILocation(line: 160, column: 4, scope: !514)
!520 = !DILocation(line: 160, column: 26, scope: !514)
!521 = !DILocation(line: 160, column: 33, scope: !514)
!522 = !DILocation(line: 160, column: 32, scope: !514)
!523 = !DILocation(line: 160, column: 30, scope: !514)
!524 = !DILocation(line: 160, column: 42, scope: !514)
!525 = !DILocation(line: 161, column: 3, scope: !514)
!526 = !DILocation(line: 162, column: 2, scope: !418)
!527 = !DILocation(line: 162, column: 13, scope: !528)
!528 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 1)
!529 = distinct !DILexicalBlock(scope: !409, file: !1, line: 162, column: 13)
!530 = !DILocation(line: 162, column: 20, scope: !528)
!531 = !DILocation(line: 162, column: 24, scope: !528)
!532 = !DILocation(line: 163, column: 11, scope: !533)
!533 = distinct !DILexicalBlock(scope: !529, file: !1, line: 162, column: 29)
!534 = !DILocation(line: 163, column: 18, scope: !533)
!535 = !DILocation(line: 163, column: 3, scope: !533)
!536 = !DILocation(line: 163, column: 26, scope: !533)
!537 = !DILocation(line: 163, column: 33, scope: !533)
!538 = !DILocation(line: 163, column: 42, scope: !533)
!539 = !DILocation(line: 163, column: 49, scope: !533)
!540 = !DILocation(line: 163, column: 40, scope: !533)
!541 = !DILocation(line: 163, column: 54, scope: !533)
!542 = !DILocation(line: 164, column: 18, scope: !533)
!543 = !DILocation(line: 164, column: 25, scope: !533)
!544 = !DILocation(line: 164, column: 3, scope: !533)
!545 = !DILocation(line: 164, column: 10, scope: !533)
!546 = !DILocation(line: 164, column: 15, scope: !533)
!547 = !DILocation(line: 165, column: 3, scope: !533)
!548 = !DILocation(line: 165, column: 10, scope: !533)
!549 = !DILocation(line: 165, column: 14, scope: !533)
!550 = !DILocation(line: 166, column: 2, scope: !533)
!551 = !DILocation(line: 168, column: 2, scope: !152)
!552 = !DILocation(line: 168, column: 2, scope: !392)
!553 = !DILocation(line: 168, column: 2, scope: !394)
!554 = !DILocation(line: 168, column: 2, scope: !396)
!555 = !DILocation(line: 174, column: 6, scope: !556)
!556 = distinct !DILexicalBlock(scope: !152, file: !1, line: 174, column: 6)
!557 = !DILocation(line: 174, column: 13, scope: !556)
!558 = !DILocation(line: 174, column: 18, scope: !556)
!559 = !DILocation(line: 174, column: 6, scope: !152)
!560 = !DILocalVariable(name: "ret", scope: !561, file: !1, line: 176, type: !445)
!561 = distinct !DILexicalBlock(scope: !562, file: !1, line: 175, column: 3)
!562 = distinct !DILexicalBlock(scope: !556, file: !1, line: 174, column: 23)
!563 = !DILocation(line: 176, column: 19, scope: !561)
!564 = !DILocation(line: 176, column: 38, scope: !561)
!565 = !DILocation(line: 176, column: 45, scope: !561)
!566 = !DILocation(line: 177, column: 6, scope: !561)
!567 = !DILocation(line: 177, column: 10, scope: !561)
!568 = !DILocation(line: 177, column: 18, scope: !561)
!569 = !DILocation(line: 178, column: 6, scope: !561)
!570 = !DILocation(line: 178, column: 13, scope: !561)
!571 = !DILocation(line: 178, column: 22, scope: !561)
!572 = !DILocation(line: 178, column: 29, scope: !561)
!573 = !DILocation(line: 179, column: 6, scope: !561)
!574 = !DILocation(line: 179, column: 13, scope: !561)
!575 = !DILocation(line: 179, column: 24, scope: !561)
!576 = !DILocation(line: 176, column: 25, scope: !561)
!577 = !DILocation(line: 180, column: 4, scope: !561)
!578 = !DILocation(line: 180, column: 4, scope: !579)
!579 = !DILexicalBlockFile(scope: !561, file: !1, discriminator: 1)
!580 = !DILocation(line: 180, column: 4, scope: !581)
!581 = !DILexicalBlockFile(scope: !561, file: !1, discriminator: 2)
!582 = !DILocation(line: 180, column: 4, scope: !583)
!583 = !DILexicalBlockFile(scope: !561, file: !1, discriminator: 3)
!584 = !DILocation(line: 181, column: 8, scope: !585)
!585 = distinct !DILexicalBlock(scope: !561, file: !1, line: 181, column: 8)
!586 = !DILocation(line: 181, column: 12, scope: !585)
!587 = !DILocation(line: 181, column: 8, scope: !561)
!588 = !DILocation(line: 182, column: 12, scope: !585)
!589 = !DILocation(line: 182, column: 5, scope: !585)
!590 = !DILocation(line: 186, column: 5, scope: !562)
!591 = !DILocation(line: 186, column: 12, scope: !562)
!592 = !DILocation(line: 186, column: 19, scope: !562)
!593 = !DILocation(line: 186, column: 27, scope: !562)
!594 = !DILocation(line: 186, column: 34, scope: !562)
!595 = !DILocation(line: 185, column: 21, scope: !562)
!596 = !DILocation(line: 185, column: 3, scope: !562)
!597 = !DILocation(line: 185, column: 10, scope: !562)
!598 = !DILocation(line: 185, column: 19, scope: !562)
!599 = !DILocation(line: 190, column: 7, scope: !600)
!600 = distinct !DILexicalBlock(scope: !562, file: !1, line: 190, column: 7)
!601 = !DILocation(line: 190, column: 14, scope: !600)
!602 = !DILocation(line: 190, column: 7, scope: !562)
!603 = !DILocation(line: 191, column: 22, scope: !600)
!604 = !DILocation(line: 191, column: 29, scope: !600)
!605 = !DILocation(line: 191, column: 4, scope: !600)
!606 = !DILocation(line: 191, column: 11, scope: !600)
!607 = !DILocation(line: 191, column: 20, scope: !600)
!608 = !DILocation(line: 194, column: 15, scope: !562)
!609 = !DILocation(line: 194, column: 22, scope: !562)
!610 = !DILocation(line: 194, column: 31, scope: !562)
!611 = !DILocation(line: 194, column: 38, scope: !562)
!612 = !DILocation(line: 194, column: 43, scope: !562)
!613 = !DILocation(line: 194, column: 50, scope: !562)
!614 = !DILocation(line: 195, column: 5, scope: !562)
!615 = !DILocation(line: 195, column: 10, scope: !562)
!616 = !DILocation(line: 195, column: 19, scope: !562)
!617 = !DILocation(line: 194, column: 3, scope: !562)
!618 = !DILocation(line: 196, column: 2, scope: !562)
!619 = !DILocation(line: 199, column: 6, scope: !620)
!620 = distinct !DILexicalBlock(scope: !152, file: !1, line: 199, column: 6)
!621 = !DILocation(line: 199, column: 13, scope: !620)
!622 = !DILocation(line: 199, column: 29, scope: !620)
!623 = !DILocation(line: 199, column: 32, scope: !624)
!624 = !DILexicalBlockFile(scope: !620, file: !1, discriminator: 1)
!625 = !DILocation(line: 199, column: 39, scope: !624)
!626 = !DILocation(line: 199, column: 46, scope: !624)
!627 = !DILocation(line: 199, column: 53, scope: !624)
!628 = !DILocation(line: 199, column: 43, scope: !624)
!629 = !DILocation(line: 199, column: 6, scope: !624)
!630 = !DILocation(line: 200, column: 3, scope: !620)
!631 = !DILocation(line: 202, column: 2, scope: !152)
!632 = !DILocation(line: 203, column: 1, scope: !152)
!633 = !DILocalVariable(name: "coder", arg: 1, scope: !157, file: !1, line: 207, type: !44)
!634 = !DILocation(line: 207, column: 30, scope: !157)
!635 = !DILocalVariable(name: "allocator", arg: 2, scope: !157, file: !1, line: 207, type: !90)
!636 = !DILocation(line: 207, column: 53, scope: !157)
!637 = !DILocation(line: 209, column: 17, scope: !157)
!638 = !DILocation(line: 209, column: 24, scope: !157)
!639 = !DILocation(line: 209, column: 30, scope: !157)
!640 = !DILocation(line: 209, column: 2, scope: !157)
!641 = !DILocation(line: 210, column: 12, scope: !157)
!642 = !DILocation(line: 210, column: 19, scope: !157)
!643 = !DILocation(line: 210, column: 27, scope: !157)
!644 = !DILocation(line: 210, column: 2, scope: !157)
!645 = !DILocation(line: 211, column: 12, scope: !157)
!646 = !DILocation(line: 211, column: 19, scope: !157)
!647 = !DILocation(line: 211, column: 2, scope: !157)
!648 = !DILocation(line: 212, column: 2, scope: !157)
!649 = !DILocalVariable(name: "coder", arg: 1, scope: !158, file: !1, line: 217, type: !44)
!650 = !DILocation(line: 217, column: 33, scope: !158)
!651 = !DILocalVariable(name: "allocator", arg: 2, scope: !158, file: !1, line: 217, type: !90)
!652 = !DILocation(line: 217, column: 56, scope: !158)
!653 = !DILocalVariable(name: "filters_null", arg: 3, scope: !158, file: !1, line: 218, type: !131)
!654 = !DILocation(line: 218, column: 22, scope: !158)
!655 = !DILocalVariable(name: "reversed_filters", arg: 4, scope: !158, file: !1, line: 219, type: !131)
!656 = !DILocation(line: 219, column: 22, scope: !158)
!657 = !DILocation(line: 223, column: 5, scope: !158)
!658 = !DILocation(line: 223, column: 12, scope: !158)
!659 = !DILocation(line: 223, column: 18, scope: !158)
!660 = !DILocation(line: 223, column: 29, scope: !158)
!661 = !DILocation(line: 223, column: 46, scope: !158)
!662 = !DILocation(line: 222, column: 9, scope: !158)
!663 = !DILocation(line: 222, column: 2, scope: !158)
!664 = !DILocalVariable(name: "coder", arg: 1, scope: !153, file: !1, line: 21, type: !44)
!665 = !DILocation(line: 21, column: 26, scope: !153)
!666 = !DILocalVariable(name: "allocator", arg: 2, scope: !153, file: !1, line: 21, type: !90)
!667 = !DILocation(line: 21, column: 49, scope: !153)
!668 = !DILocalVariable(name: "in", arg: 3, scope: !153, file: !1, line: 22, type: !103)
!669 = !DILocation(line: 22, column: 32, scope: !153)
!670 = !DILocalVariable(name: "in_pos", arg: 4, scope: !153, file: !1, line: 22, type: !106)
!671 = !DILocation(line: 22, column: 58, scope: !153)
!672 = !DILocalVariable(name: "in_size", arg: 5, scope: !153, file: !1, line: 23, type: !57)
!673 = !DILocation(line: 23, column: 10, scope: !153)
!674 = !DILocalVariable(name: "out", arg: 6, scope: !153, file: !1, line: 23, type: !108)
!675 = !DILocation(line: 23, column: 42, scope: !153)
!676 = !DILocalVariable(name: "out_pos", arg: 7, scope: !153, file: !1, line: 24, type: !106)
!677 = !DILocation(line: 24, column: 25, scope: !153)
!678 = !DILocalVariable(name: "out_size", arg: 8, scope: !153, file: !1, line: 24, type: !57)
!679 = !DILocation(line: 24, column: 41, scope: !153)
!680 = !DILocalVariable(name: "action", arg: 9, scope: !153, file: !1, line: 24, type: !109)
!681 = !DILocation(line: 24, column: 63, scope: !153)
!682 = !DILocation(line: 26, column: 2, scope: !153)
!683 = !DILocation(line: 26, column: 2, scope: !684)
!684 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 1)
!685 = !DILocation(line: 26, column: 2, scope: !686)
!686 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 2)
!687 = !DILocation(line: 26, column: 2, scope: !688)
!688 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 3)
!689 = !DILocation(line: 28, column: 6, scope: !690)
!690 = distinct !DILexicalBlock(scope: !153, file: !1, line: 28, column: 6)
!691 = !DILocation(line: 28, column: 13, scope: !690)
!692 = !DILocation(line: 28, column: 18, scope: !690)
!693 = !DILocation(line: 28, column: 23, scope: !690)
!694 = !DILocation(line: 28, column: 6, scope: !153)
!695 = !DILocation(line: 29, column: 15, scope: !696)
!696 = distinct !DILexicalBlock(scope: !690, file: !1, line: 28, column: 32)
!697 = !DILocation(line: 29, column: 19, scope: !696)
!698 = !DILocation(line: 29, column: 27, scope: !696)
!699 = !DILocation(line: 29, column: 36, scope: !696)
!700 = !DILocation(line: 29, column: 41, scope: !696)
!701 = !DILocation(line: 29, column: 50, scope: !696)
!702 = !DILocation(line: 29, column: 3, scope: !696)
!703 = !DILocation(line: 32, column: 7, scope: !704)
!704 = distinct !DILexicalBlock(scope: !696, file: !1, line: 32, column: 7)
!705 = !DILocation(line: 32, column: 14, scope: !704)
!706 = !DILocation(line: 32, column: 25, scope: !704)
!707 = !DILocation(line: 32, column: 28, scope: !708)
!708 = !DILexicalBlockFile(scope: !704, file: !1, discriminator: 1)
!709 = !DILocation(line: 32, column: 35, scope: !708)
!710 = !DILocation(line: 33, column: 5, scope: !704)
!711 = !DILocation(line: 33, column: 9, scope: !708)
!712 = !DILocation(line: 33, column: 8, scope: !708)
!713 = !DILocation(line: 33, column: 19, scope: !708)
!714 = !DILocation(line: 33, column: 16, scope: !708)
!715 = !DILocation(line: 32, column: 7, scope: !716)
!716 = !DILexicalBlockFile(scope: !696, file: !1, discriminator: 2)
!717 = !DILocation(line: 34, column: 4, scope: !704)
!718 = !DILocation(line: 34, column: 11, scope: !704)
!719 = !DILocation(line: 34, column: 27, scope: !704)
!720 = !DILocation(line: 36, column: 2, scope: !696)
!721 = !DILocalVariable(name: "ret", scope: !722, file: !1, line: 38, type: !445)
!722 = distinct !DILexicalBlock(scope: !690, file: !1, line: 36, column: 9)
!723 = !DILocation(line: 38, column: 18, scope: !722)
!724 = !DILocation(line: 38, column: 24, scope: !722)
!725 = !DILocation(line: 38, column: 31, scope: !722)
!726 = !DILocation(line: 38, column: 36, scope: !722)
!727 = !DILocation(line: 39, column: 5, scope: !722)
!728 = !DILocation(line: 39, column: 12, scope: !722)
!729 = !DILocation(line: 39, column: 17, scope: !722)
!730 = !DILocation(line: 39, column: 24, scope: !722)
!731 = !DILocation(line: 40, column: 5, scope: !722)
!732 = !DILocation(line: 40, column: 9, scope: !722)
!733 = !DILocation(line: 40, column: 17, scope: !722)
!734 = !DILocation(line: 41, column: 5, scope: !722)
!735 = !DILocation(line: 41, column: 10, scope: !722)
!736 = !DILocation(line: 41, column: 19, scope: !722)
!737 = !DILocation(line: 41, column: 29, scope: !722)
!738 = !DILocation(line: 43, column: 7, scope: !739)
!739 = distinct !DILexicalBlock(scope: !722, file: !1, line: 43, column: 7)
!740 = !DILocation(line: 43, column: 11, scope: !739)
!741 = !DILocation(line: 43, column: 7, scope: !722)
!742 = !DILocation(line: 44, column: 4, scope: !743)
!743 = distinct !DILexicalBlock(scope: !739, file: !1, line: 43, column: 31)
!744 = !DILocation(line: 44, column: 4, scope: !745)
!745 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 1)
!746 = !DILocation(line: 44, column: 4, scope: !747)
!747 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 2)
!748 = !DILocation(line: 44, column: 4, scope: !749)
!749 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 3)
!750 = !DILocation(line: 44, column: 4, scope: !751)
!751 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 4)
!752 = !DILocation(line: 46, column: 4, scope: !743)
!753 = !DILocation(line: 46, column: 11, scope: !743)
!754 = !DILocation(line: 46, column: 27, scope: !743)
!755 = !DILocation(line: 48, column: 3, scope: !743)
!756 = !DILocation(line: 48, column: 14, scope: !757)
!757 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 1)
!758 = distinct !DILexicalBlock(scope: !739, file: !1, line: 48, column: 14)
!759 = !DILocation(line: 48, column: 18, scope: !757)
!760 = !DILocation(line: 49, column: 11, scope: !761)
!761 = distinct !DILexicalBlock(scope: !758, file: !1, line: 48, column: 30)
!762 = !DILocation(line: 49, column: 4, scope: !761)
!763 = !DILocation(line: 53, column: 2, scope: !153)
!764 = !DILocation(line: 54, column: 1, scope: !153)
!765 = !DILocalVariable(name: "coder", arg: 1, scope: !154, file: !1, line: 58, type: !44)
!766 = !DILocation(line: 58, column: 25, scope: !154)
!767 = !DILocalVariable(name: "buffer", arg: 2, scope: !154, file: !1, line: 58, type: !66)
!768 = !DILocation(line: 58, column: 41, scope: !154)
!769 = !DILocalVariable(name: "size", arg: 3, scope: !154, file: !1, line: 58, type: !57)
!770 = !DILocation(line: 58, column: 56, scope: !154)
!771 = !DILocalVariable(name: "filtered", scope: !154, file: !1, line: 60, type: !425)
!772 = !DILocation(line: 60, column: 15, scope: !154)
!773 = !DILocation(line: 60, column: 26, scope: !154)
!774 = !DILocation(line: 60, column: 33, scope: !154)
!775 = !DILocation(line: 60, column: 40, scope: !154)
!776 = !DILocation(line: 60, column: 47, scope: !154)
!777 = !DILocation(line: 61, column: 4, scope: !154)
!778 = !DILocation(line: 61, column: 11, scope: !154)
!779 = !DILocation(line: 61, column: 20, scope: !154)
!780 = !DILocation(line: 61, column: 27, scope: !154)
!781 = !DILocation(line: 62, column: 4, scope: !154)
!782 = !DILocation(line: 62, column: 12, scope: !154)
!783 = !DILocation(line: 63, column: 20, scope: !154)
!784 = !DILocation(line: 63, column: 2, scope: !154)
!785 = !DILocation(line: 63, column: 9, scope: !154)
!786 = !DILocation(line: 63, column: 17, scope: !154)
!787 = !DILocation(line: 64, column: 9, scope: !154)
!788 = !DILocation(line: 64, column: 2, scope: !154)
