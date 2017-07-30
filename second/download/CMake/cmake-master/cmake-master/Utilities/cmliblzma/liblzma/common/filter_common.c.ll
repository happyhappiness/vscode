; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_common.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i64, i64, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_filter_coder = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i64 (i8*)* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }

@features = internal constant [10 x %struct.anon] [%struct.anon { i64 4611686018427387905, i64 112, i8 0, i8 1, i8 1 }, %struct.anon { i64 33, i64 112, i8 0, i8 1, i8 1 }, %struct.anon { i64 4, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 5, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 6, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 7, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 8, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 9, i64 4, i8 1, i8 0, i8 0 }, %struct.anon { i64 3, i64 40, i8 1, i8 0, i8 0 }, %struct.anon { i64 -1, i64 0, i8 0, i8 0, i8 0 }], align 16
@.str = private unnamed_addr constant [11 x i8] c"i <= 4 + 1\00", align 1
@.str.1 = private unnamed_addr constant [85 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_common.c\00", align 1
@__PRETTY_FUNCTION__.lzma_filters_copy = private unnamed_addr constant [81 x i8] c"lzma_ret lzma_filters_copy(const lzma_filter *, lzma_filter *, lzma_allocator *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_filters_copy(%struct.lzma_filter* %src, %struct.lzma_filter* %dest, %struct.lzma_allocator* %allocator) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %src.addr = alloca %struct.lzma_filter*, align 8
  %dest.addr = alloca %struct.lzma_filter*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i = alloca i64, align 8
  %ret = alloca i32, align 4
  %j = alloca i64, align 8
  store %struct.lzma_filter* %src, %struct.lzma_filter** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %src.addr, metadata !172, metadata !173), !dbg !174
  store %struct.lzma_filter* %dest, %struct.lzma_filter** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %dest.addr, metadata !175, metadata !173), !dbg !176
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !177, metadata !173), !dbg !178
  call void @llvm.dbg.declare(metadata i64* %i, metadata !179, metadata !173), !dbg !180
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !181, metadata !173), !dbg !182
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !183
  %cmp = icmp eq %struct.lzma_filter* %0, null, !dbg !185
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !186

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !187
  %cmp1 = icmp eq %struct.lzma_filter* %1, null, !dbg !189
  br i1 %cmp1, label %if.then, label %if.end, !dbg !190

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !191
  br label %return, !dbg !191

if.end:                                           ; preds = %lor.lhs.false
  store i64 0, i64* %i, align 8, !dbg !192
  br label %for.cond, !dbg !194

for.cond:                                         ; preds = %for.inc42, %if.end
  %2 = load i64, i64* %i, align 8, !dbg !195
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !198
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %3, i64 %2, !dbg !198
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !199
  %4 = load i64, i64* %id, align 8, !dbg !199
  %cmp2 = icmp ne i64 %4, -1, !dbg !200
  br i1 %cmp2, label %for.body, label %for.end44, !dbg !201

for.body:                                         ; preds = %for.cond
  %5 = load i64, i64* %i, align 8, !dbg !202
  %cmp3 = icmp eq i64 %5, 4, !dbg !205
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !206

if.then4:                                         ; preds = %for.body
  store i32 8, i32* %ret, align 4, !dbg !207
  br label %error, !dbg !209

if.end5:                                          ; preds = %for.body
  %6 = load i64, i64* %i, align 8, !dbg !210
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !211
  %arrayidx6 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %7, i64 %6, !dbg !211
  %id7 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx6, i32 0, i32 0, !dbg !212
  %8 = load i64, i64* %id7, align 8, !dbg !212
  %9 = load i64, i64* %i, align 8, !dbg !213
  %10 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !214
  %arrayidx8 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %10, i64 %9, !dbg !214
  %id9 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx8, i32 0, i32 0, !dbg !215
  store i64 %8, i64* %id9, align 8, !dbg !216
  %11 = load i64, i64* %i, align 8, !dbg !217
  %12 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !219
  %arrayidx10 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %12, i64 %11, !dbg !219
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx10, i32 0, i32 1, !dbg !220
  %13 = load i8*, i8** %options, align 8, !dbg !220
  %cmp11 = icmp eq i8* %13, null, !dbg !221
  br i1 %cmp11, label %if.then12, label %if.else, !dbg !222

if.then12:                                        ; preds = %if.end5
  %14 = load i64, i64* %i, align 8, !dbg !223
  %15 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !225
  %arrayidx13 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %15, i64 %14, !dbg !225
  %options14 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx13, i32 0, i32 1, !dbg !226
  store i8* null, i8** %options14, align 8, !dbg !227
  br label %if.end41, !dbg !228

if.else:                                          ; preds = %if.end5
  call void @llvm.dbg.declare(metadata i64* %j, metadata !229, metadata !173), !dbg !231
  store i64 0, i64* %j, align 8, !dbg !232
  br label %for.cond15, !dbg !234

for.cond15:                                       ; preds = %for.inc, %if.else
  %16 = load i64, i64* %i, align 8, !dbg !235
  %17 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !238
  %arrayidx16 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %17, i64 %16, !dbg !238
  %id17 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx16, i32 0, i32 0, !dbg !239
  %18 = load i64, i64* %id17, align 8, !dbg !239
  %19 = load i64, i64* %j, align 8, !dbg !240
  %arrayidx18 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %19, !dbg !241
  %id19 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx18, i32 0, i32 0, !dbg !242
  %20 = load i64, i64* %id19, align 8, !dbg !242
  %cmp20 = icmp ne i64 %18, %20, !dbg !243
  br i1 %cmp20, label %for.body21, label %for.end, !dbg !244

for.body21:                                       ; preds = %for.cond15
  %21 = load i64, i64* %j, align 8, !dbg !245
  %arrayidx22 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %21, !dbg !248
  %id23 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx22, i32 0, i32 0, !dbg !249
  %22 = load i64, i64* %id23, align 8, !dbg !249
  %cmp24 = icmp eq i64 %22, -1, !dbg !250
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !251

if.then25:                                        ; preds = %for.body21
  store i32 8, i32* %ret, align 4, !dbg !252
  br label %error, !dbg !254

if.end26:                                         ; preds = %for.body21
  br label %for.inc, !dbg !255

for.inc:                                          ; preds = %if.end26
  %23 = load i64, i64* %j, align 8, !dbg !256
  %inc = add i64 %23, 1, !dbg !256
  store i64 %inc, i64* %j, align 8, !dbg !256
  br label %for.cond15, !dbg !258

for.end:                                          ; preds = %for.cond15
  %24 = load i64, i64* %j, align 8, !dbg !259
  %arrayidx27 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %24, !dbg !260
  %options_size = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx27, i32 0, i32 1, !dbg !261
  %25 = load i64, i64* %options_size, align 8, !dbg !261
  %26 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !262
  %call = call noalias i8* @lzma_alloc(i64 %25, %struct.lzma_allocator* %26), !dbg !263
  %27 = load i64, i64* %i, align 8, !dbg !264
  %28 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !265
  %arrayidx28 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %28, i64 %27, !dbg !265
  %options29 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx28, i32 0, i32 1, !dbg !266
  store i8* %call, i8** %options29, align 8, !dbg !267
  %29 = load i64, i64* %i, align 8, !dbg !268
  %30 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !270
  %arrayidx30 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %30, i64 %29, !dbg !270
  %options31 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx30, i32 0, i32 1, !dbg !271
  %31 = load i8*, i8** %options31, align 8, !dbg !271
  %cmp32 = icmp eq i8* %31, null, !dbg !272
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !273

if.then33:                                        ; preds = %for.end
  store i32 5, i32* %ret, align 4, !dbg !274
  br label %error, !dbg !276

if.end34:                                         ; preds = %for.end
  %32 = load i64, i64* %i, align 8, !dbg !277
  %33 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !278
  %arrayidx35 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %33, i64 %32, !dbg !278
  %options36 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx35, i32 0, i32 1, !dbg !279
  %34 = load i8*, i8** %options36, align 8, !dbg !279
  %35 = load i64, i64* %i, align 8, !dbg !280
  %36 = load %struct.lzma_filter*, %struct.lzma_filter** %src.addr, align 8, !dbg !281
  %arrayidx37 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %36, i64 %35, !dbg !281
  %options38 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx37, i32 0, i32 1, !dbg !282
  %37 = load i8*, i8** %options38, align 8, !dbg !282
  %38 = load i64, i64* %j, align 8, !dbg !283
  %arrayidx39 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %38, !dbg !284
  %options_size40 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx39, i32 0, i32 1, !dbg !285
  %39 = load i64, i64* %options_size40, align 8, !dbg !285
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %34, i8* %37, i64 %39, i32 1, i1 false), !dbg !286
  br label %if.end41

if.end41:                                         ; preds = %if.end34, %if.then12
  br label %for.inc42, !dbg !287

for.inc42:                                        ; preds = %if.end41
  %40 = load i64, i64* %i, align 8, !dbg !288
  %inc43 = add i64 %40, 1, !dbg !288
  store i64 %inc43, i64* %i, align 8, !dbg !288
  br label %for.cond, !dbg !290

for.end44:                                        ; preds = %for.cond
  %41 = load i64, i64* %i, align 8, !dbg !291
  %cmp45 = icmp ule i64 %41, 5, !dbg !291
  br i1 %cmp45, label %cond.true, label %cond.false, !dbg !291

cond.true:                                        ; preds = %for.end44
  br label %cond.end, !dbg !292

cond.false:                                       ; preds = %for.end44
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 177, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @__PRETTY_FUNCTION__.lzma_filters_copy, i32 0, i32 0)) #5, !dbg !294
  unreachable, !dbg !294
                                                  ; No predecessors!
  br label %cond.end, !dbg !296

cond.end:                                         ; preds = %42, %cond.true
  %43 = load i64, i64* %i, align 8, !dbg !298
  %44 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !299
  %arrayidx46 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %44, i64 %43, !dbg !299
  %id47 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx46, i32 0, i32 0, !dbg !300
  store i64 -1, i64* %id47, align 8, !dbg !301
  %45 = load i64, i64* %i, align 8, !dbg !302
  %46 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !303
  %arrayidx48 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %46, i64 %45, !dbg !303
  %options49 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx48, i32 0, i32 1, !dbg !304
  store i8* null, i8** %options49, align 8, !dbg !305
  store i32 0, i32* %retval, align 4, !dbg !306
  br label %return, !dbg !306

error:                                            ; preds = %if.then33, %if.then25, %if.then4
  br label %while.cond, !dbg !307

while.cond:                                       ; preds = %while.body, %error
  %47 = load i64, i64* %i, align 8, !dbg !308
  %dec = add i64 %47, -1, !dbg !308
  store i64 %dec, i64* %i, align 8, !dbg !308
  %cmp50 = icmp ugt i64 %47, 0, !dbg !309
  br i1 %cmp50, label %while.body, label %while.end, !dbg !310

while.body:                                       ; preds = %while.cond
  %48 = load i64, i64* %i, align 8, !dbg !311
  %49 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !313
  %arrayidx51 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %49, i64 %48, !dbg !313
  %options52 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx51, i32 0, i32 1, !dbg !314
  %50 = load i8*, i8** %options52, align 8, !dbg !314
  %51 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !315
  call void @lzma_free(i8* %50, %struct.lzma_allocator* %51), !dbg !316
  %52 = load i64, i64* %i, align 8, !dbg !317
  %53 = load %struct.lzma_filter*, %struct.lzma_filter** %dest.addr, align 8, !dbg !318
  %arrayidx53 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %53, i64 %52, !dbg !318
  %options54 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx53, i32 0, i32 1, !dbg !319
  store i8* null, i8** %options54, align 8, !dbg !320
  br label %while.cond, !dbg !321

while.end:                                        ; preds = %while.cond
  %54 = load i32, i32* %ret, align 4, !dbg !322
  store i32 %54, i32* %retval, align 4, !dbg !323
  br label %return, !dbg !323

return:                                           ; preds = %while.end, %cond.end, %if.then
  %55 = load i32, i32* %retval, align 4, !dbg !324
  ret i32 %55, !dbg !324
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %options, %struct.lzma_filter_coder* (i64)* %coder_find, i1 zeroext %is_encoder) #0 !dbg !68 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca %struct.lzma_filter*, align 8
  %coder_find.addr = alloca %struct.lzma_filter_coder* (i64)*, align 8
  %is_encoder.addr = alloca i8, align 1
  %filters = alloca [5 x %struct.lzma_filter_info_s], align 16
  %count = alloca i64, align 8
  %i = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %j = alloca i64, align 8
  %fc = alloca %struct.lzma_filter_coder*, align 8
  %fc24 = alloca %struct.lzma_filter_coder*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !325, metadata !173), !dbg !326
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !327, metadata !173), !dbg !328
  store %struct.lzma_filter* %options, %struct.lzma_filter** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %options.addr, metadata !329, metadata !173), !dbg !330
  store %struct.lzma_filter_coder* (i64)* %coder_find, %struct.lzma_filter_coder* (i64)** %coder_find.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_coder* (i64)** %coder_find.addr, metadata !331, metadata !173), !dbg !332
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !333, metadata !173), !dbg !334
  call void @llvm.dbg.declare(metadata [5 x %struct.lzma_filter_info_s]* %filters, metadata !335, metadata !173), !dbg !339
  call void @llvm.dbg.declare(metadata i64* %count, metadata !340, metadata !173), !dbg !341
  call void @llvm.dbg.declare(metadata i64* %i, metadata !342, metadata !173), !dbg !343
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !344, metadata !173), !dbg !345
  br label %do.body, !dbg !346

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !347, metadata !173), !dbg !350
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !351
  %call = call i32 @validate_chain(%struct.lzma_filter* %0, i64* %count), !dbg !351
  store i32 %call, i32* %ret_, align 4, !dbg !351
  %1 = load i32, i32* %ret_, align 4, !dbg !351
  %cmp = icmp ne i32 %1, 0, !dbg !351
  br i1 %cmp, label %if.then, label %if.end, !dbg !351

if.then:                                          ; preds = %do.body
  %2 = load i32, i32* %ret_, align 4, !dbg !353
  store i32 %2, i32* %retval, align 4, !dbg !353
  br label %return, !dbg !353

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !356

do.end:                                           ; preds = %if.end
  %3 = load i8, i8* %is_encoder.addr, align 1, !dbg !358
  %tobool = trunc i8 %3 to i1, !dbg !358
  br i1 %tobool, label %if.then1, label %if.else, !dbg !360

if.then1:                                         ; preds = %do.end
  store i64 0, i64* %i, align 8, !dbg !361
  br label %for.cond, !dbg !364

for.cond:                                         ; preds = %for.inc, %if.then1
  %4 = load i64, i64* %i, align 8, !dbg !365
  %5 = load i64, i64* %count, align 8, !dbg !368
  %cmp2 = icmp ult i64 %4, %5, !dbg !369
  br i1 %cmp2, label %for.body, label %for.end, !dbg !370

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %j, metadata !371, metadata !173), !dbg !374
  %6 = load i64, i64* %count, align 8, !dbg !375
  %7 = load i64, i64* %i, align 8, !dbg !376
  %sub = sub i64 %6, %7, !dbg !377
  %sub3 = sub i64 %sub, 1, !dbg !378
  store i64 %sub3, i64* %j, align 8, !dbg !374
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_coder** %fc, metadata !379, metadata !173), !dbg !381
  %8 = load %struct.lzma_filter_coder* (i64)*, %struct.lzma_filter_coder* (i64)** %coder_find.addr, align 8, !dbg !382
  %9 = load i64, i64* %i, align 8, !dbg !383
  %10 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !384
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %10, i64 %9, !dbg !384
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !385
  %11 = load i64, i64* %id, align 8, !dbg !385
  %call4 = call %struct.lzma_filter_coder* %8(i64 %11), !dbg !382
  store %struct.lzma_filter_coder* %call4, %struct.lzma_filter_coder** %fc, align 8, !dbg !381
  %12 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !386
  %cmp5 = icmp eq %struct.lzma_filter_coder* %12, null, !dbg !388
  br i1 %cmp5, label %if.then7, label %lor.lhs.false, !dbg !389

lor.lhs.false:                                    ; preds = %for.body
  %13 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !390
  %init = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %13, i32 0, i32 1, !dbg !392
  %14 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init, align 8, !dbg !392
  %cmp6 = icmp eq i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %14, null, !dbg !393
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !394

if.then7:                                         ; preds = %lor.lhs.false, %for.body
  store i32 8, i32* %retval, align 4, !dbg !395
  br label %return, !dbg !395

if.end8:                                          ; preds = %lor.lhs.false
  %15 = load i64, i64* %i, align 8, !dbg !396
  %16 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !397
  %arrayidx9 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %16, i64 %15, !dbg !397
  %id10 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx9, i32 0, i32 0, !dbg !398
  %17 = load i64, i64* %id10, align 8, !dbg !398
  %18 = load i64, i64* %j, align 8, !dbg !399
  %arrayidx11 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %18, !dbg !400
  %id12 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx11, i32 0, i32 0, !dbg !401
  store i64 %17, i64* %id12, align 8, !dbg !402
  %19 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !403
  %init13 = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %19, i32 0, i32 1, !dbg !404
  %20 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init13, align 8, !dbg !404
  %21 = load i64, i64* %j, align 8, !dbg !405
  %arrayidx14 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %21, !dbg !406
  %init15 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx14, i32 0, i32 1, !dbg !407
  %init16 = bitcast {}** %init15 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !407
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %20, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init16, align 8, !dbg !408
  %22 = load i64, i64* %i, align 8, !dbg !409
  %23 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !410
  %arrayidx17 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %23, i64 %22, !dbg !410
  %options18 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx17, i32 0, i32 1, !dbg !411
  %24 = load i8*, i8** %options18, align 8, !dbg !411
  %25 = load i64, i64* %j, align 8, !dbg !412
  %arrayidx19 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %25, !dbg !413
  %options20 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx19, i32 0, i32 2, !dbg !414
  store i8* %24, i8** %options20, align 8, !dbg !415
  br label %for.inc, !dbg !416

for.inc:                                          ; preds = %if.end8
  %26 = load i64, i64* %i, align 8, !dbg !417
  %inc = add i64 %26, 1, !dbg !417
  store i64 %inc, i64* %i, align 8, !dbg !417
  br label %for.cond, !dbg !419

for.end:                                          ; preds = %for.cond
  br label %if.end49, !dbg !420

if.else:                                          ; preds = %do.end
  store i64 0, i64* %i, align 8, !dbg !421
  br label %for.cond21, !dbg !424

for.cond21:                                       ; preds = %for.inc46, %if.else
  %27 = load i64, i64* %i, align 8, !dbg !425
  %28 = load i64, i64* %count, align 8, !dbg !428
  %cmp22 = icmp ult i64 %27, %28, !dbg !429
  br i1 %cmp22, label %for.body23, label %for.end48, !dbg !430

for.body23:                                       ; preds = %for.cond21
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_coder** %fc24, metadata !431, metadata !173), !dbg !433
  %29 = load %struct.lzma_filter_coder* (i64)*, %struct.lzma_filter_coder* (i64)** %coder_find.addr, align 8, !dbg !434
  %30 = load i64, i64* %i, align 8, !dbg !435
  %31 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !436
  %arrayidx25 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %31, i64 %30, !dbg !436
  %id26 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx25, i32 0, i32 0, !dbg !437
  %32 = load i64, i64* %id26, align 8, !dbg !437
  %call27 = call %struct.lzma_filter_coder* %29(i64 %32), !dbg !434
  store %struct.lzma_filter_coder* %call27, %struct.lzma_filter_coder** %fc24, align 8, !dbg !433
  %33 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc24, align 8, !dbg !438
  %cmp28 = icmp eq %struct.lzma_filter_coder* %33, null, !dbg !440
  br i1 %cmp28, label %if.then32, label %lor.lhs.false29, !dbg !441

lor.lhs.false29:                                  ; preds = %for.body23
  %34 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc24, align 8, !dbg !442
  %init30 = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %34, i32 0, i32 1, !dbg !444
  %35 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init30, align 8, !dbg !444
  %cmp31 = icmp eq i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %35, null, !dbg !445
  br i1 %cmp31, label %if.then32, label %if.end33, !dbg !446

if.then32:                                        ; preds = %lor.lhs.false29, %for.body23
  store i32 8, i32* %retval, align 4, !dbg !447
  br label %return, !dbg !447

if.end33:                                         ; preds = %lor.lhs.false29
  %36 = load i64, i64* %i, align 8, !dbg !448
  %37 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !449
  %arrayidx34 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %37, i64 %36, !dbg !449
  %id35 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx34, i32 0, i32 0, !dbg !450
  %38 = load i64, i64* %id35, align 8, !dbg !450
  %39 = load i64, i64* %i, align 8, !dbg !451
  %arrayidx36 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %39, !dbg !452
  %id37 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx36, i32 0, i32 0, !dbg !453
  store i64 %38, i64* %id37, align 8, !dbg !454
  %40 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc24, align 8, !dbg !455
  %init38 = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %40, i32 0, i32 1, !dbg !456
  %41 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init38, align 8, !dbg !456
  %42 = load i64, i64* %i, align 8, !dbg !457
  %arrayidx39 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %42, !dbg !458
  %init40 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx39, i32 0, i32 1, !dbg !459
  %init41 = bitcast {}** %init40 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !459
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %41, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init41, align 8, !dbg !460
  %43 = load i64, i64* %i, align 8, !dbg !461
  %44 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !462
  %arrayidx42 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %44, i64 %43, !dbg !462
  %options43 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx42, i32 0, i32 1, !dbg !463
  %45 = load i8*, i8** %options43, align 8, !dbg !463
  %46 = load i64, i64* %i, align 8, !dbg !464
  %arrayidx44 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %46, !dbg !465
  %options45 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx44, i32 0, i32 2, !dbg !466
  store i8* %45, i8** %options45, align 8, !dbg !467
  br label %for.inc46, !dbg !468

for.inc46:                                        ; preds = %if.end33
  %47 = load i64, i64* %i, align 8, !dbg !469
  %inc47 = add i64 %47, 1, !dbg !469
  store i64 %inc47, i64* %i, align 8, !dbg !469
  br label %for.cond21, !dbg !471

for.end48:                                        ; preds = %for.cond21
  br label %if.end49

if.end49:                                         ; preds = %for.end48, %for.end
  %48 = load i64, i64* %count, align 8, !dbg !472
  %arrayidx50 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %48, !dbg !473
  %id51 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx50, i32 0, i32 0, !dbg !474
  store i64 -1, i64* %id51, align 8, !dbg !475
  %49 = load i64, i64* %count, align 8, !dbg !476
  %arrayidx52 = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 %49, !dbg !477
  %init53 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx52, i32 0, i32 1, !dbg !478
  %init54 = bitcast {}** %init53 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !478
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* null, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init54, align 8, !dbg !479
  %50 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !480
  %51 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !481
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter_info_s], [5 x %struct.lzma_filter_info_s]* %filters, i32 0, i32 0, !dbg !482
  %call55 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %50, %struct.lzma_allocator* %51, %struct.lzma_filter_info_s* %arraydecay), !dbg !483
  store i32 %call55, i32* %ret, align 4, !dbg !484
  %52 = load i32, i32* %ret, align 4, !dbg !485
  %cmp56 = icmp ne i32 %52, 0, !dbg !487
  br i1 %cmp56, label %if.then57, label %if.end58, !dbg !488

if.then57:                                        ; preds = %if.end49
  %53 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !489
  %54 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !490
  call void @lzma_next_end(%struct.lzma_next_coder_s* %53, %struct.lzma_allocator* %54), !dbg !491
  br label %if.end58, !dbg !491

if.end58:                                         ; preds = %if.then57, %if.end49
  %55 = load i32, i32* %ret, align 4, !dbg !492
  store i32 %55, i32* %retval, align 4, !dbg !493
  br label %return, !dbg !493

return:                                           ; preds = %if.end58, %if.then32, %if.then7, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !494
  ret i32 %56, !dbg !494
}

; Function Attrs: nounwind uwtable
define internal i32 @validate_chain(%struct.lzma_filter* %filters, i64* %count) #0 !dbg !153 {
entry:
  %retval = alloca i32, align 4
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %count.addr = alloca i64*, align 8
  %changes_size_count = alloca i64, align 8
  %non_last_ok = alloca i8, align 1
  %last_ok = alloca i8, align 1
  %i = alloca i64, align 8
  %j = alloca i64, align 8
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !495, metadata !173), !dbg !496
  store i64* %count, i64** %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %count.addr, metadata !497, metadata !173), !dbg !498
  call void @llvm.dbg.declare(metadata i64* %changes_size_count, metadata !499, metadata !173), !dbg !500
  store i64 0, i64* %changes_size_count, align 8, !dbg !500
  call void @llvm.dbg.declare(metadata i8* %non_last_ok, metadata !501, metadata !173), !dbg !502
  store i8 1, i8* %non_last_ok, align 1, !dbg !502
  call void @llvm.dbg.declare(metadata i8* %last_ok, metadata !503, metadata !173), !dbg !504
  store i8 0, i8* %last_ok, align 1, !dbg !504
  call void @llvm.dbg.declare(metadata i64* %i, metadata !505, metadata !173), !dbg !506
  store i64 0, i64* %i, align 8, !dbg !506
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !507
  %cmp = icmp eq %struct.lzma_filter* %0, null, !dbg !509
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !510

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !511
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %1, i64 0, !dbg !511
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !513
  %2 = load i64, i64* %id, align 8, !dbg !513
  %cmp1 = icmp eq i64 %2, -1, !dbg !514
  br i1 %cmp1, label %if.then, label %if.end, !dbg !515

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !516
  br label %return, !dbg !516

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !517

do.body:                                          ; preds = %do.cond, %if.end
  call void @llvm.dbg.declare(metadata i64* %j, metadata !518, metadata !173), !dbg !520
  store i64 0, i64* %j, align 8, !dbg !521
  br label %for.cond, !dbg !523

for.cond:                                         ; preds = %for.inc, %do.body
  %3 = load i64, i64* %i, align 8, !dbg !524
  %4 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !527
  %arrayidx2 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %4, i64 %3, !dbg !527
  %id3 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx2, i32 0, i32 0, !dbg !528
  %5 = load i64, i64* %id3, align 8, !dbg !528
  %6 = load i64, i64* %j, align 8, !dbg !529
  %arrayidx4 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %6, !dbg !530
  %id5 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx4, i32 0, i32 0, !dbg !531
  %7 = load i64, i64* %id5, align 8, !dbg !531
  %cmp6 = icmp ne i64 %5, %7, !dbg !532
  br i1 %cmp6, label %for.body, label %for.end, !dbg !533

for.body:                                         ; preds = %for.cond
  %8 = load i64, i64* %j, align 8, !dbg !534
  %arrayidx7 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %8, !dbg !536
  %id8 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx7, i32 0, i32 0, !dbg !537
  %9 = load i64, i64* %id8, align 8, !dbg !537
  %cmp9 = icmp eq i64 %9, -1, !dbg !538
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !539

if.then10:                                        ; preds = %for.body
  store i32 8, i32* %retval, align 4, !dbg !540
  br label %return, !dbg !540

if.end11:                                         ; preds = %for.body
  br label %for.inc, !dbg !541

for.inc:                                          ; preds = %if.end11
  %10 = load i64, i64* %j, align 8, !dbg !543
  %inc = add i64 %10, 1, !dbg !543
  store i64 %inc, i64* %j, align 8, !dbg !543
  br label %for.cond, !dbg !545

for.end:                                          ; preds = %for.cond
  %11 = load i8, i8* %non_last_ok, align 1, !dbg !546
  %tobool = trunc i8 %11 to i1, !dbg !546
  br i1 %tobool, label %if.end13, label %if.then12, !dbg !548

if.then12:                                        ; preds = %for.end
  store i32 8, i32* %retval, align 4, !dbg !549
  br label %return, !dbg !549

if.end13:                                         ; preds = %for.end
  %12 = load i64, i64* %j, align 8, !dbg !550
  %arrayidx14 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %12, !dbg !551
  %non_last_ok15 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx14, i32 0, i32 2, !dbg !552
  %13 = load i8, i8* %non_last_ok15, align 8, !dbg !552
  %tobool16 = trunc i8 %13 to i1, !dbg !552
  %frombool = zext i1 %tobool16 to i8, !dbg !553
  store i8 %frombool, i8* %non_last_ok, align 1, !dbg !553
  %14 = load i64, i64* %j, align 8, !dbg !554
  %arrayidx17 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %14, !dbg !555
  %last_ok18 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx17, i32 0, i32 3, !dbg !556
  %15 = load i8, i8* %last_ok18, align 1, !dbg !556
  %tobool19 = trunc i8 %15 to i1, !dbg !556
  %frombool20 = zext i1 %tobool19 to i8, !dbg !557
  store i8 %frombool20, i8* %last_ok, align 1, !dbg !557
  %16 = load i64, i64* %j, align 8, !dbg !558
  %arrayidx21 = getelementptr inbounds [10 x %struct.anon], [10 x %struct.anon]* @features, i64 0, i64 %16, !dbg !559
  %changes_size = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx21, i32 0, i32 4, !dbg !560
  %17 = load i8, i8* %changes_size, align 2, !dbg !560
  %tobool22 = trunc i8 %17 to i1, !dbg !560
  %conv = zext i1 %tobool22 to i64, !dbg !559
  %18 = load i64, i64* %changes_size_count, align 8, !dbg !561
  %add = add i64 %18, %conv, !dbg !561
  store i64 %add, i64* %changes_size_count, align 8, !dbg !561
  br label %do.cond, !dbg !562

do.cond:                                          ; preds = %if.end13
  %19 = load i64, i64* %i, align 8, !dbg !563
  %inc23 = add i64 %19, 1, !dbg !563
  store i64 %inc23, i64* %i, align 8, !dbg !563
  %20 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !565
  %arrayidx24 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %20, i64 %inc23, !dbg !565
  %id25 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx24, i32 0, i32 0, !dbg !566
  %21 = load i64, i64* %id25, align 8, !dbg !566
  %cmp26 = icmp ne i64 %21, -1, !dbg !567
  br i1 %cmp26, label %do.body, label %do.end, !dbg !568

do.end:                                           ; preds = %do.cond
  %22 = load i64, i64* %i, align 8, !dbg !569
  %cmp28 = icmp ugt i64 %22, 4, !dbg !571
  br i1 %cmp28, label %if.then35, label %lor.lhs.false30, !dbg !572

lor.lhs.false30:                                  ; preds = %do.end
  %23 = load i8, i8* %last_ok, align 1, !dbg !573
  %tobool31 = trunc i8 %23 to i1, !dbg !573
  br i1 %tobool31, label %lor.lhs.false32, label %if.then35, !dbg !575

lor.lhs.false32:                                  ; preds = %lor.lhs.false30
  %24 = load i64, i64* %changes_size_count, align 8, !dbg !576
  %cmp33 = icmp ugt i64 %24, 3, !dbg !578
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !579

if.then35:                                        ; preds = %lor.lhs.false32, %lor.lhs.false30, %do.end
  store i32 8, i32* %retval, align 4, !dbg !580
  br label %return, !dbg !580

if.end36:                                         ; preds = %lor.lhs.false32
  %25 = load i64, i64* %i, align 8, !dbg !581
  %26 = load i64*, i64** %count.addr, align 8, !dbg !582
  store i64 %25, i64* %26, align 8, !dbg !583
  store i32 0, i32* %retval, align 4, !dbg !584
  br label %return, !dbg !584

return:                                           ; preds = %if.end36, %if.then35, %if.then12, %if.then10, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !585
  ret i32 %27, !dbg !585
}

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define i64 @lzma_raw_coder_memusage(%struct.lzma_filter_coder* (i64)* %coder_find, %struct.lzma_filter* %filters) #0 !dbg !150 {
entry:
  %retval = alloca i64, align 8
  %coder_find.addr = alloca %struct.lzma_filter_coder* (i64)*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %total = alloca i64, align 8
  %i = alloca i64, align 8
  %tmp = alloca i64, align 8
  %fc = alloca %struct.lzma_filter_coder*, align 8
  %usage = alloca i64, align 8
  store %struct.lzma_filter_coder* (i64)* %coder_find, %struct.lzma_filter_coder* (i64)** %coder_find.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_coder* (i64)** %coder_find.addr, metadata !586, metadata !173), !dbg !587
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !588, metadata !173), !dbg !589
  call void @llvm.dbg.declare(metadata i64* %total, metadata !590, metadata !173), !dbg !591
  store i64 0, i64* %total, align 8, !dbg !591
  call void @llvm.dbg.declare(metadata i64* %i, metadata !592, metadata !173), !dbg !593
  store i64 0, i64* %i, align 8, !dbg !593
  call void @llvm.dbg.declare(metadata i64* %tmp, metadata !594, metadata !173), !dbg !596
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !597
  %call = call i32 @validate_chain(%struct.lzma_filter* %0, i64* %tmp), !dbg !599
  %cmp = icmp ne i32 %call, 0, !dbg !600
  br i1 %cmp, label %if.then, label %if.end, !dbg !601

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !602
  br label %return, !dbg !602

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !603

do.body:                                          ; preds = %do.cond, %if.end
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_coder** %fc, metadata !604, metadata !173), !dbg !606
  %1 = load %struct.lzma_filter_coder* (i64)*, %struct.lzma_filter_coder* (i64)** %coder_find.addr, align 8, !dbg !607
  %2 = load i64, i64* %i, align 8, !dbg !608
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !609
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %3, i64 %2, !dbg !609
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !610
  %4 = load i64, i64* %id, align 8, !dbg !610
  %call2 = call %struct.lzma_filter_coder* %1(i64 %4), !dbg !607
  store %struct.lzma_filter_coder* %call2, %struct.lzma_filter_coder** %fc, align 8, !dbg !606
  %5 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !611
  %cmp3 = icmp eq %struct.lzma_filter_coder* %5, null, !dbg !613
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !614

if.then4:                                         ; preds = %do.body
  store i64 -1, i64* %retval, align 8, !dbg !615
  br label %return, !dbg !615

if.end5:                                          ; preds = %do.body
  %6 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !616
  %memusage = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %6, i32 0, i32 2, !dbg !618
  %7 = load i64 (i8*)*, i64 (i8*)** %memusage, align 8, !dbg !618
  %cmp6 = icmp eq i64 (i8*)* %7, null, !dbg !619
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !620

if.then7:                                         ; preds = %if.end5
  %8 = load i64, i64* %total, align 8, !dbg !621
  %add = add i64 %8, 1024, !dbg !621
  store i64 %add, i64* %total, align 8, !dbg !621
  br label %if.end16, !dbg !623

if.else:                                          ; preds = %if.end5
  call void @llvm.dbg.declare(metadata i64* %usage, metadata !624, metadata !173), !dbg !627
  %9 = load %struct.lzma_filter_coder*, %struct.lzma_filter_coder** %fc, align 8, !dbg !628
  %memusage9 = getelementptr inbounds %struct.lzma_filter_coder, %struct.lzma_filter_coder* %9, i32 0, i32 2, !dbg !629
  %10 = load i64 (i8*)*, i64 (i8*)** %memusage9, align 8, !dbg !629
  %11 = load i64, i64* %i, align 8, !dbg !630
  %12 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !631
  %arrayidx10 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %12, i64 %11, !dbg !631
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx10, i32 0, i32 1, !dbg !632
  %13 = load i8*, i8** %options, align 8, !dbg !632
  %call11 = call i64 %10(i8* %13), !dbg !628
  store i64 %call11, i64* %usage, align 8, !dbg !627
  %14 = load i64, i64* %usage, align 8, !dbg !633
  %cmp12 = icmp eq i64 %14, -1, !dbg !635
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !636

if.then13:                                        ; preds = %if.else
  store i64 -1, i64* %retval, align 8, !dbg !637
  br label %return, !dbg !637

if.end14:                                         ; preds = %if.else
  %15 = load i64, i64* %usage, align 8, !dbg !638
  %16 = load i64, i64* %total, align 8, !dbg !639
  %add15 = add i64 %16, %15, !dbg !639
  store i64 %add15, i64* %total, align 8, !dbg !639
  br label %if.end16

if.end16:                                         ; preds = %if.end14, %if.then7
  br label %do.cond, !dbg !640

do.cond:                                          ; preds = %if.end16
  %17 = load i64, i64* %i, align 8, !dbg !641
  %inc = add i64 %17, 1, !dbg !641
  store i64 %inc, i64* %i, align 8, !dbg !641
  %18 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !643
  %arrayidx17 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %18, i64 %inc, !dbg !643
  %id18 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx17, i32 0, i32 0, !dbg !644
  %19 = load i64, i64* %id18, align 8, !dbg !644
  %cmp19 = icmp ne i64 %19, -1, !dbg !645
  br i1 %cmp19, label %do.body, label %do.end, !dbg !646

do.end:                                           ; preds = %do.cond
  %20 = load i64, i64* %total, align 8, !dbg !647
  %add20 = add i64 %20, 32768, !dbg !648
  store i64 %add20, i64* %retval, align 8, !dbg !649
  br label %return, !dbg !649

return:                                           ; preds = %do.end, %if.then13, %if.then4, %if.then
  %21 = load i64, i64* %retval, align 8, !dbg !650
  ret i64 %21, !dbg !650
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!169, !170}
!llvm.ident = !{!171}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !33, globals: !156)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_common.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!33 = !{!34, !68, !150, !153}
!34 = distinct !DISubprogram(name: "lzma_filters_copy", scope: !1, file: !1, line: 125, type: !35, isLocal: false, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !51, !52}
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
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !54)
!54 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !55)
!55 = !{!56, !62, !66}
!56 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !54, file: !4, line: 376, baseType: !57, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DISubroutineType(types: !59)
!59 = !{!32, !32, !60, !60}
!60 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !61, line: 62, baseType: !49)
!61 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!62 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !54, file: !4, line: 390, baseType: !63, size: 64, align: 64, offset: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!64 = !DISubroutineType(types: !65)
!65 = !{null, !32, !32}
!66 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !54, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!67 = !{}
!68 = distinct !DISubprogram(name: "lzma_raw_coder_init", scope: !1, file: !1, line: 244, type: !69, isLocal: false, isDefinition: true, scopeLine: 247, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!69 = !DISubroutineType(types: !70)
!70 = !{!37, !71, !52, !38, !119, !149}
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !73, line: 75, baseType: !74)
!73 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!74 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !73, line: 119, size: 512, align: 64, elements: !75)
!75 = !{!76, !80, !81, !83, !98, !103, !110, !115}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !74, file: !73, line: 121, baseType: !77, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !73, line: 73, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !73, line: 73, flags: DIFlagFwdDecl)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !74, file: !73, line: 125, baseType: !45, size: 64, align: 64, offset: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !74, file: !73, line: 131, baseType: !82, size: 64, align: 64, offset: 128)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !48, line: 122, baseType: !49)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !74, file: !73, line: 134, baseType: !84, size: 64, align: 64, offset: 192)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !73, line: 89, baseType: !85)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!37, !77, !52, !88, !93, !60, !95, !93, !60, !97}
!88 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !89)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !91)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !48, line: 48, baseType: !92)
!92 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !94)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !96)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !74, file: !73, line: 139, baseType: !99, size: 64, align: 64, offset: 256)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !73, line: 97, baseType: !100)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{null, !77, !52}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !74, file: !73, line: 143, baseType: !104, size: 64, align: 64, offset: 320)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !108}
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !78)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !74, file: !73, line: 147, baseType: !111, size: 64, align: 64, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DISubroutineType(types: !113)
!113 = !{!37, !77, !114, !114, !47}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !74, file: !73, line: 152, baseType: !116, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!37, !77, !52, !38, !38}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_find", file: !120, line: 35, baseType: !121)
!120 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DISubroutineType(types: !123)
!123 = !{!124, !45}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !126)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_coder", file: !120, line: 32, baseType: !127)
!127 = !DICompositeType(tag: DW_TAG_structure_type, file: !120, line: 20, size: 192, align: 64, elements: !128)
!128 = !{!129, !130, !143}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !127, file: !120, line: 22, baseType: !45, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !127, file: !120, line: 26, baseType: !131, size: 64, align: 64, offset: 64)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !73, line: 81, baseType: !132)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DISubroutineType(types: !134)
!134 = !{!37, !71, !52, !135}
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !136, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !137)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !73, line: 77, baseType: !138)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !73, line: 104, size: 192, align: 64, elements: !139)
!139 = !{!140, !141, !142}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !138, file: !73, line: 107, baseType: !45, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !138, file: !73, line: 111, baseType: !131, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !73, line: 114, baseType: !32, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !127, file: !120, line: 30, baseType: !144, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!47, !147}
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!149 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!150 = distinct !DISubprogram(name: "lzma_raw_coder_memusage", scope: !1, file: !1, line: 300, type: !151, isLocal: false, isDefinition: true, scopeLine: 302, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!151 = !DISubroutineType(types: !152)
!152 = !{!47, !119, !38}
!153 = distinct !DISubprogram(name: "validate_chain", scope: !1, file: !1, line: 195, type: !154, isLocal: true, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!154 = !DISubroutineType(types: !155)
!155 = !{!37, !38, !94}
!156 = !{!157}
!157 = !DIGlobalVariable(name: "features", scope: !0, file: !1, line: 36, type: !158, isLocal: true, isDefinition: true, variable: [10 x %struct.anon]* @features)
!158 = !DICompositeType(tag: DW_TAG_array_type, baseType: !159, size: 1920, align: 64, elements: !167)
!159 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !160)
!160 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 16, size: 192, align: 64, elements: !161)
!161 = !{!162, !163, !164, !165, !166}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !160, file: !1, line: 18, baseType: !45, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "options_size", scope: !160, file: !1, line: 21, baseType: !60, size: 64, align: 64, offset: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "non_last_ok", scope: !160, file: !1, line: 25, baseType: !149, size: 8, align: 8, offset: 128)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "last_ok", scope: !160, file: !1, line: 29, baseType: !149, size: 8, align: 8, offset: 136)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "changes_size", scope: !160, file: !1, line: 34, baseType: !149, size: 8, align: 8, offset: 144)
!167 = !{!168}
!168 = !DISubrange(count: 10)
!169 = !{i32 2, !"Dwarf Version", i32 4}
!170 = !{i32 2, !"Debug Info Version", i32 3}
!171 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!172 = !DILocalVariable(name: "src", arg: 1, scope: !34, file: !1, line: 125, type: !38)
!173 = !DIExpression()
!174 = !DILocation(line: 125, column: 38, scope: !34)
!175 = !DILocalVariable(name: "dest", arg: 2, scope: !34, file: !1, line: 125, type: !51)
!176 = !DILocation(line: 125, column: 56, scope: !34)
!177 = !DILocalVariable(name: "allocator", arg: 3, scope: !34, file: !1, line: 126, type: !52)
!178 = !DILocation(line: 126, column: 19, scope: !34)
!179 = !DILocalVariable(name: "i", scope: !34, file: !1, line: 128, type: !60)
!180 = !DILocation(line: 128, column: 9, scope: !34)
!181 = !DILocalVariable(name: "ret", scope: !34, file: !1, line: 129, type: !37)
!182 = !DILocation(line: 129, column: 11, scope: !34)
!183 = !DILocation(line: 131, column: 6, scope: !184)
!184 = distinct !DILexicalBlock(scope: !34, file: !1, line: 131, column: 6)
!185 = !DILocation(line: 131, column: 10, scope: !184)
!186 = !DILocation(line: 131, column: 18, scope: !184)
!187 = !DILocation(line: 131, column: 21, scope: !188)
!188 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 1)
!189 = !DILocation(line: 131, column: 26, scope: !188)
!190 = !DILocation(line: 131, column: 6, scope: !188)
!191 = !DILocation(line: 132, column: 3, scope: !184)
!192 = !DILocation(line: 134, column: 9, scope: !193)
!193 = distinct !DILexicalBlock(scope: !34, file: !1, line: 134, column: 2)
!194 = !DILocation(line: 134, column: 7, scope: !193)
!195 = !DILocation(line: 134, column: 18, scope: !196)
!196 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!197 = distinct !DILexicalBlock(scope: !193, file: !1, line: 134, column: 2)
!198 = !DILocation(line: 134, column: 14, scope: !196)
!199 = !DILocation(line: 134, column: 21, scope: !196)
!200 = !DILocation(line: 134, column: 24, scope: !196)
!201 = !DILocation(line: 134, column: 2, scope: !196)
!202 = !DILocation(line: 137, column: 7, scope: !203)
!203 = distinct !DILexicalBlock(scope: !204, file: !1, line: 137, column: 7)
!204 = distinct !DILexicalBlock(scope: !197, file: !1, line: 134, column: 50)
!205 = !DILocation(line: 137, column: 9, scope: !203)
!206 = !DILocation(line: 137, column: 7, scope: !204)
!207 = !DILocation(line: 138, column: 8, scope: !208)
!208 = distinct !DILexicalBlock(scope: !203, file: !1, line: 137, column: 30)
!209 = !DILocation(line: 139, column: 4, scope: !208)
!210 = !DILocation(line: 142, column: 20, scope: !204)
!211 = !DILocation(line: 142, column: 16, scope: !204)
!212 = !DILocation(line: 142, column: 23, scope: !204)
!213 = !DILocation(line: 142, column: 8, scope: !204)
!214 = !DILocation(line: 142, column: 3, scope: !204)
!215 = !DILocation(line: 142, column: 11, scope: !204)
!216 = !DILocation(line: 142, column: 14, scope: !204)
!217 = !DILocation(line: 144, column: 11, scope: !218)
!218 = distinct !DILexicalBlock(scope: !204, file: !1, line: 144, column: 7)
!219 = !DILocation(line: 144, column: 7, scope: !218)
!220 = !DILocation(line: 144, column: 14, scope: !218)
!221 = !DILocation(line: 144, column: 22, scope: !218)
!222 = !DILocation(line: 144, column: 7, scope: !204)
!223 = !DILocation(line: 145, column: 9, scope: !224)
!224 = distinct !DILexicalBlock(scope: !218, file: !1, line: 144, column: 31)
!225 = !DILocation(line: 145, column: 4, scope: !224)
!226 = !DILocation(line: 145, column: 12, scope: !224)
!227 = !DILocation(line: 145, column: 20, scope: !224)
!228 = !DILocation(line: 146, column: 3, scope: !224)
!229 = !DILocalVariable(name: "j", scope: !230, file: !1, line: 155, type: !60)
!230 = distinct !DILexicalBlock(scope: !218, file: !1, line: 146, column: 10)
!231 = !DILocation(line: 155, column: 11, scope: !230)
!232 = !DILocation(line: 156, column: 11, scope: !233)
!233 = distinct !DILexicalBlock(scope: !230, file: !1, line: 156, column: 4)
!234 = !DILocation(line: 156, column: 9, scope: !233)
!235 = !DILocation(line: 156, column: 20, scope: !236)
!236 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 1)
!237 = distinct !DILexicalBlock(scope: !233, file: !1, line: 156, column: 4)
!238 = !DILocation(line: 156, column: 16, scope: !236)
!239 = !DILocation(line: 156, column: 23, scope: !236)
!240 = !DILocation(line: 156, column: 38, scope: !236)
!241 = !DILocation(line: 156, column: 29, scope: !236)
!242 = !DILocation(line: 156, column: 41, scope: !236)
!243 = !DILocation(line: 156, column: 26, scope: !236)
!244 = !DILocation(line: 156, column: 4, scope: !236)
!245 = !DILocation(line: 157, column: 18, scope: !246)
!246 = distinct !DILexicalBlock(scope: !247, file: !1, line: 157, column: 9)
!247 = distinct !DILexicalBlock(scope: !237, file: !1, line: 156, column: 50)
!248 = !DILocation(line: 157, column: 9, scope: !246)
!249 = !DILocation(line: 157, column: 21, scope: !246)
!250 = !DILocation(line: 157, column: 24, scope: !246)
!251 = !DILocation(line: 157, column: 9, scope: !247)
!252 = !DILocation(line: 158, column: 10, scope: !253)
!253 = distinct !DILexicalBlock(scope: !246, file: !1, line: 157, column: 45)
!254 = !DILocation(line: 159, column: 6, scope: !253)
!255 = !DILocation(line: 161, column: 4, scope: !247)
!256 = !DILocation(line: 156, column: 45, scope: !257)
!257 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 2)
!258 = !DILocation(line: 156, column: 4, scope: !257)
!259 = !DILocation(line: 164, column: 42, scope: !230)
!260 = !DILocation(line: 164, column: 33, scope: !230)
!261 = !DILocation(line: 164, column: 45, scope: !230)
!262 = !DILocation(line: 165, column: 6, scope: !230)
!263 = !DILocation(line: 164, column: 22, scope: !230)
!264 = !DILocation(line: 164, column: 9, scope: !230)
!265 = !DILocation(line: 164, column: 4, scope: !230)
!266 = !DILocation(line: 164, column: 12, scope: !230)
!267 = !DILocation(line: 164, column: 20, scope: !230)
!268 = !DILocation(line: 166, column: 13, scope: !269)
!269 = distinct !DILexicalBlock(scope: !230, file: !1, line: 166, column: 8)
!270 = !DILocation(line: 166, column: 8, scope: !269)
!271 = !DILocation(line: 166, column: 16, scope: !269)
!272 = !DILocation(line: 166, column: 24, scope: !269)
!273 = !DILocation(line: 166, column: 8, scope: !230)
!274 = !DILocation(line: 167, column: 9, scope: !275)
!275 = distinct !DILexicalBlock(scope: !269, file: !1, line: 166, column: 33)
!276 = !DILocation(line: 168, column: 5, scope: !275)
!277 = !DILocation(line: 171, column: 16, scope: !230)
!278 = !DILocation(line: 171, column: 11, scope: !230)
!279 = !DILocation(line: 171, column: 19, scope: !230)
!280 = !DILocation(line: 171, column: 32, scope: !230)
!281 = !DILocation(line: 171, column: 28, scope: !230)
!282 = !DILocation(line: 171, column: 35, scope: !230)
!283 = !DILocation(line: 172, column: 15, scope: !230)
!284 = !DILocation(line: 172, column: 6, scope: !230)
!285 = !DILocation(line: 172, column: 18, scope: !230)
!286 = !DILocation(line: 171, column: 4, scope: !230)
!287 = !DILocation(line: 174, column: 2, scope: !204)
!288 = !DILocation(line: 134, column: 45, scope: !289)
!289 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 2)
!290 = !DILocation(line: 134, column: 2, scope: !289)
!291 = !DILocation(line: 177, column: 2, scope: !34)
!292 = !DILocation(line: 177, column: 2, scope: !293)
!293 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 1)
!294 = !DILocation(line: 177, column: 2, scope: !295)
!295 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 2)
!296 = !DILocation(line: 177, column: 2, scope: !297)
!297 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 3)
!298 = !DILocation(line: 178, column: 7, scope: !34)
!299 = !DILocation(line: 178, column: 2, scope: !34)
!300 = !DILocation(line: 178, column: 10, scope: !34)
!301 = !DILocation(line: 178, column: 13, scope: !34)
!302 = !DILocation(line: 179, column: 7, scope: !34)
!303 = !DILocation(line: 179, column: 2, scope: !34)
!304 = !DILocation(line: 179, column: 10, scope: !34)
!305 = !DILocation(line: 179, column: 18, scope: !34)
!306 = !DILocation(line: 181, column: 2, scope: !34)
!307 = !DILocation(line: 185, column: 2, scope: !34)
!308 = !DILocation(line: 185, column: 10, scope: !293)
!309 = !DILocation(line: 185, column: 13, scope: !293)
!310 = !DILocation(line: 185, column: 2, scope: !293)
!311 = !DILocation(line: 186, column: 18, scope: !312)
!312 = distinct !DILexicalBlock(scope: !34, file: !1, line: 185, column: 18)
!313 = !DILocation(line: 186, column: 13, scope: !312)
!314 = !DILocation(line: 186, column: 21, scope: !312)
!315 = !DILocation(line: 186, column: 30, scope: !312)
!316 = !DILocation(line: 186, column: 3, scope: !312)
!317 = !DILocation(line: 187, column: 8, scope: !312)
!318 = !DILocation(line: 187, column: 3, scope: !312)
!319 = !DILocation(line: 187, column: 11, scope: !312)
!320 = !DILocation(line: 187, column: 19, scope: !312)
!321 = !DILocation(line: 185, column: 2, scope: !295)
!322 = !DILocation(line: 190, column: 9, scope: !34)
!323 = !DILocation(line: 190, column: 2, scope: !34)
!324 = !DILocation(line: 191, column: 1, scope: !34)
!325 = !DILocalVariable(name: "next", arg: 1, scope: !68, file: !1, line: 244, type: !71)
!326 = !DILocation(line: 244, column: 38, scope: !68)
!327 = !DILocalVariable(name: "allocator", arg: 2, scope: !68, file: !1, line: 244, type: !52)
!328 = !DILocation(line: 244, column: 60, scope: !68)
!329 = !DILocalVariable(name: "options", arg: 3, scope: !68, file: !1, line: 245, type: !38)
!330 = !DILocation(line: 245, column: 22, scope: !68)
!331 = !DILocalVariable(name: "coder_find", arg: 4, scope: !68, file: !1, line: 246, type: !119)
!332 = !DILocation(line: 246, column: 20, scope: !68)
!333 = !DILocalVariable(name: "is_encoder", arg: 5, scope: !68, file: !1, line: 246, type: !149)
!334 = !DILocation(line: 246, column: 37, scope: !68)
!335 = !DILocalVariable(name: "filters", scope: !68, file: !1, line: 248, type: !336)
!336 = !DICompositeType(tag: DW_TAG_array_type, baseType: !137, size: 960, align: 64, elements: !337)
!337 = !{!338}
!338 = !DISubrange(count: 5)
!339 = !DILocation(line: 248, column: 19, scope: !68)
!340 = !DILocalVariable(name: "count", scope: !68, file: !1, line: 249, type: !60)
!341 = !DILocation(line: 249, column: 9, scope: !68)
!342 = !DILocalVariable(name: "i", scope: !68, file: !1, line: 250, type: !60)
!343 = !DILocation(line: 250, column: 9, scope: !68)
!344 = !DILocalVariable(name: "ret", scope: !68, file: !1, line: 251, type: !37)
!345 = !DILocation(line: 251, column: 11, scope: !68)
!346 = !DILocation(line: 254, column: 2, scope: !68)
!347 = !DILocalVariable(name: "ret_", scope: !348, file: !1, line: 254, type: !349)
!348 = distinct !DILexicalBlock(scope: !68, file: !1, line: 254, column: 2)
!349 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!350 = !DILocation(line: 254, column: 2, scope: !348)
!351 = !DILocation(line: 254, column: 2, scope: !352)
!352 = !DILexicalBlockFile(scope: !348, file: !1, discriminator: 1)
!353 = !DILocation(line: 254, column: 2, scope: !354)
!354 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 2)
!355 = distinct !DILexicalBlock(scope: !348, file: !1, line: 254, column: 2)
!356 = !DILocation(line: 254, column: 2, scope: !357)
!357 = !DILexicalBlockFile(scope: !348, file: !1, discriminator: 3)
!358 = !DILocation(line: 257, column: 6, scope: !359)
!359 = distinct !DILexicalBlock(scope: !68, file: !1, line: 257, column: 6)
!360 = !DILocation(line: 257, column: 6, scope: !68)
!361 = !DILocation(line: 258, column: 10, scope: !362)
!362 = distinct !DILexicalBlock(scope: !363, file: !1, line: 258, column: 3)
!363 = distinct !DILexicalBlock(scope: !359, file: !1, line: 257, column: 18)
!364 = !DILocation(line: 258, column: 8, scope: !362)
!365 = !DILocation(line: 258, column: 15, scope: !366)
!366 = !DILexicalBlockFile(scope: !367, file: !1, discriminator: 1)
!367 = distinct !DILexicalBlock(scope: !362, file: !1, line: 258, column: 3)
!368 = !DILocation(line: 258, column: 19, scope: !366)
!369 = !DILocation(line: 258, column: 17, scope: !366)
!370 = !DILocation(line: 258, column: 3, scope: !366)
!371 = !DILocalVariable(name: "j", scope: !372, file: !1, line: 262, type: !373)
!372 = distinct !DILexicalBlock(scope: !367, file: !1, line: 258, column: 31)
!373 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !60)
!374 = !DILocation(line: 262, column: 17, scope: !372)
!375 = !DILocation(line: 262, column: 21, scope: !372)
!376 = !DILocation(line: 262, column: 29, scope: !372)
!377 = !DILocation(line: 262, column: 27, scope: !372)
!378 = !DILocation(line: 262, column: 31, scope: !372)
!379 = !DILocalVariable(name: "fc", scope: !372, file: !1, line: 264, type: !380)
!380 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !124)
!381 = !DILocation(line: 264, column: 35, scope: !372)
!382 = !DILocation(line: 265, column: 8, scope: !372)
!383 = !DILocation(line: 265, column: 27, scope: !372)
!384 = !DILocation(line: 265, column: 19, scope: !372)
!385 = !DILocation(line: 265, column: 30, scope: !372)
!386 = !DILocation(line: 266, column: 8, scope: !387)
!387 = distinct !DILexicalBlock(scope: !372, file: !1, line: 266, column: 8)
!388 = !DILocation(line: 266, column: 11, scope: !387)
!389 = !DILocation(line: 266, column: 19, scope: !387)
!390 = !DILocation(line: 266, column: 22, scope: !391)
!391 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 1)
!392 = !DILocation(line: 266, column: 26, scope: !391)
!393 = !DILocation(line: 266, column: 31, scope: !391)
!394 = !DILocation(line: 266, column: 8, scope: !391)
!395 = !DILocation(line: 267, column: 5, scope: !387)
!396 = !DILocation(line: 269, column: 28, scope: !372)
!397 = !DILocation(line: 269, column: 20, scope: !372)
!398 = !DILocation(line: 269, column: 31, scope: !372)
!399 = !DILocation(line: 269, column: 12, scope: !372)
!400 = !DILocation(line: 269, column: 4, scope: !372)
!401 = !DILocation(line: 269, column: 15, scope: !372)
!402 = !DILocation(line: 269, column: 18, scope: !372)
!403 = !DILocation(line: 270, column: 22, scope: !372)
!404 = !DILocation(line: 270, column: 26, scope: !372)
!405 = !DILocation(line: 270, column: 12, scope: !372)
!406 = !DILocation(line: 270, column: 4, scope: !372)
!407 = !DILocation(line: 270, column: 15, scope: !372)
!408 = !DILocation(line: 270, column: 20, scope: !372)
!409 = !DILocation(line: 271, column: 33, scope: !372)
!410 = !DILocation(line: 271, column: 25, scope: !372)
!411 = !DILocation(line: 271, column: 36, scope: !372)
!412 = !DILocation(line: 271, column: 12, scope: !372)
!413 = !DILocation(line: 271, column: 4, scope: !372)
!414 = !DILocation(line: 271, column: 15, scope: !372)
!415 = !DILocation(line: 271, column: 23, scope: !372)
!416 = !DILocation(line: 272, column: 3, scope: !372)
!417 = !DILocation(line: 258, column: 26, scope: !418)
!418 = !DILexicalBlockFile(scope: !367, file: !1, discriminator: 2)
!419 = !DILocation(line: 258, column: 3, scope: !418)
!420 = !DILocation(line: 273, column: 2, scope: !363)
!421 = !DILocation(line: 274, column: 10, scope: !422)
!422 = distinct !DILexicalBlock(scope: !423, file: !1, line: 274, column: 3)
!423 = distinct !DILexicalBlock(scope: !359, file: !1, line: 273, column: 9)
!424 = !DILocation(line: 274, column: 8, scope: !422)
!425 = !DILocation(line: 274, column: 15, scope: !426)
!426 = !DILexicalBlockFile(scope: !427, file: !1, discriminator: 1)
!427 = distinct !DILexicalBlock(scope: !422, file: !1, line: 274, column: 3)
!428 = !DILocation(line: 274, column: 19, scope: !426)
!429 = !DILocation(line: 274, column: 17, scope: !426)
!430 = !DILocation(line: 274, column: 3, scope: !426)
!431 = !DILocalVariable(name: "fc", scope: !432, file: !1, line: 275, type: !380)
!432 = distinct !DILexicalBlock(scope: !427, file: !1, line: 274, column: 31)
!433 = !DILocation(line: 275, column: 35, scope: !432)
!434 = !DILocation(line: 276, column: 8, scope: !432)
!435 = !DILocation(line: 276, column: 27, scope: !432)
!436 = !DILocation(line: 276, column: 19, scope: !432)
!437 = !DILocation(line: 276, column: 30, scope: !432)
!438 = !DILocation(line: 277, column: 8, scope: !439)
!439 = distinct !DILexicalBlock(scope: !432, file: !1, line: 277, column: 8)
!440 = !DILocation(line: 277, column: 11, scope: !439)
!441 = !DILocation(line: 277, column: 19, scope: !439)
!442 = !DILocation(line: 277, column: 22, scope: !443)
!443 = !DILexicalBlockFile(scope: !439, file: !1, discriminator: 1)
!444 = !DILocation(line: 277, column: 26, scope: !443)
!445 = !DILocation(line: 277, column: 31, scope: !443)
!446 = !DILocation(line: 277, column: 8, scope: !443)
!447 = !DILocation(line: 278, column: 5, scope: !439)
!448 = !DILocation(line: 280, column: 28, scope: !432)
!449 = !DILocation(line: 280, column: 20, scope: !432)
!450 = !DILocation(line: 280, column: 31, scope: !432)
!451 = !DILocation(line: 280, column: 12, scope: !432)
!452 = !DILocation(line: 280, column: 4, scope: !432)
!453 = !DILocation(line: 280, column: 15, scope: !432)
!454 = !DILocation(line: 280, column: 18, scope: !432)
!455 = !DILocation(line: 281, column: 22, scope: !432)
!456 = !DILocation(line: 281, column: 26, scope: !432)
!457 = !DILocation(line: 281, column: 12, scope: !432)
!458 = !DILocation(line: 281, column: 4, scope: !432)
!459 = !DILocation(line: 281, column: 15, scope: !432)
!460 = !DILocation(line: 281, column: 20, scope: !432)
!461 = !DILocation(line: 282, column: 33, scope: !432)
!462 = !DILocation(line: 282, column: 25, scope: !432)
!463 = !DILocation(line: 282, column: 36, scope: !432)
!464 = !DILocation(line: 282, column: 12, scope: !432)
!465 = !DILocation(line: 282, column: 4, scope: !432)
!466 = !DILocation(line: 282, column: 15, scope: !432)
!467 = !DILocation(line: 282, column: 23, scope: !432)
!468 = !DILocation(line: 283, column: 3, scope: !432)
!469 = !DILocation(line: 274, column: 26, scope: !470)
!470 = !DILexicalBlockFile(scope: !427, file: !1, discriminator: 2)
!471 = !DILocation(line: 274, column: 3, scope: !470)
!472 = !DILocation(line: 287, column: 10, scope: !68)
!473 = !DILocation(line: 287, column: 2, scope: !68)
!474 = !DILocation(line: 287, column: 17, scope: !68)
!475 = !DILocation(line: 287, column: 20, scope: !68)
!476 = !DILocation(line: 288, column: 10, scope: !68)
!477 = !DILocation(line: 288, column: 2, scope: !68)
!478 = !DILocation(line: 288, column: 17, scope: !68)
!479 = !DILocation(line: 288, column: 22, scope: !68)
!480 = !DILocation(line: 291, column: 30, scope: !68)
!481 = !DILocation(line: 291, column: 36, scope: !68)
!482 = !DILocation(line: 291, column: 47, scope: !68)
!483 = !DILocation(line: 291, column: 8, scope: !68)
!484 = !DILocation(line: 291, column: 6, scope: !68)
!485 = !DILocation(line: 292, column: 6, scope: !486)
!486 = distinct !DILexicalBlock(scope: !68, file: !1, line: 292, column: 6)
!487 = !DILocation(line: 292, column: 10, scope: !486)
!488 = !DILocation(line: 292, column: 6, scope: !68)
!489 = !DILocation(line: 293, column: 17, scope: !486)
!490 = !DILocation(line: 293, column: 23, scope: !486)
!491 = !DILocation(line: 293, column: 3, scope: !486)
!492 = !DILocation(line: 295, column: 9, scope: !68)
!493 = !DILocation(line: 295, column: 2, scope: !68)
!494 = !DILocation(line: 296, column: 1, scope: !68)
!495 = !DILocalVariable(name: "filters", arg: 1, scope: !153, file: !1, line: 195, type: !38)
!496 = !DILocation(line: 195, column: 35, scope: !153)
!497 = !DILocalVariable(name: "count", arg: 2, scope: !153, file: !1, line: 195, type: !94)
!498 = !DILocation(line: 195, column: 52, scope: !153)
!499 = !DILocalVariable(name: "changes_size_count", scope: !153, file: !1, line: 199, type: !60)
!500 = !DILocation(line: 199, column: 9, scope: !153)
!501 = !DILocalVariable(name: "non_last_ok", scope: !153, file: !1, line: 202, type: !149)
!502 = !DILocation(line: 202, column: 7, scope: !153)
!503 = !DILocalVariable(name: "last_ok", scope: !153, file: !1, line: 207, type: !149)
!504 = !DILocation(line: 207, column: 7, scope: !153)
!505 = !DILocalVariable(name: "i", scope: !153, file: !1, line: 209, type: !60)
!506 = !DILocation(line: 209, column: 9, scope: !153)
!507 = !DILocation(line: 212, column: 6, scope: !508)
!508 = distinct !DILexicalBlock(scope: !153, file: !1, line: 212, column: 6)
!509 = !DILocation(line: 212, column: 14, scope: !508)
!510 = !DILocation(line: 212, column: 22, scope: !508)
!511 = !DILocation(line: 212, column: 25, scope: !512)
!512 = !DILexicalBlockFile(scope: !508, file: !1, discriminator: 1)
!513 = !DILocation(line: 212, column: 36, scope: !512)
!514 = !DILocation(line: 212, column: 39, scope: !512)
!515 = !DILocation(line: 212, column: 6, scope: !512)
!516 = !DILocation(line: 213, column: 3, scope: !508)
!517 = !DILocation(line: 215, column: 2, scope: !153)
!518 = !DILocalVariable(name: "j", scope: !519, file: !1, line: 216, type: !60)
!519 = distinct !DILexicalBlock(scope: !153, file: !1, line: 215, column: 5)
!520 = !DILocation(line: 216, column: 10, scope: !519)
!521 = !DILocation(line: 217, column: 10, scope: !522)
!522 = distinct !DILexicalBlock(scope: !519, file: !1, line: 217, column: 3)
!523 = !DILocation(line: 217, column: 8, scope: !522)
!524 = !DILocation(line: 217, column: 23, scope: !525)
!525 = !DILexicalBlockFile(scope: !526, file: !1, discriminator: 1)
!526 = distinct !DILexicalBlock(scope: !522, file: !1, line: 217, column: 3)
!527 = !DILocation(line: 217, column: 15, scope: !525)
!528 = !DILocation(line: 217, column: 26, scope: !525)
!529 = !DILocation(line: 217, column: 41, scope: !525)
!530 = !DILocation(line: 217, column: 32, scope: !525)
!531 = !DILocation(line: 217, column: 44, scope: !525)
!532 = !DILocation(line: 217, column: 29, scope: !525)
!533 = !DILocation(line: 217, column: 3, scope: !525)
!534 = !DILocation(line: 218, column: 17, scope: !535)
!535 = distinct !DILexicalBlock(scope: !526, file: !1, line: 218, column: 8)
!536 = !DILocation(line: 218, column: 8, scope: !535)
!537 = !DILocation(line: 218, column: 20, scope: !535)
!538 = !DILocation(line: 218, column: 23, scope: !535)
!539 = !DILocation(line: 218, column: 8, scope: !526)
!540 = !DILocation(line: 219, column: 5, scope: !535)
!541 = !DILocation(line: 218, column: 26, scope: !542)
!542 = !DILexicalBlockFile(scope: !535, file: !1, discriminator: 1)
!543 = !DILocation(line: 217, column: 48, scope: !544)
!544 = !DILexicalBlockFile(scope: !526, file: !1, discriminator: 2)
!545 = !DILocation(line: 217, column: 3, scope: !544)
!546 = !DILocation(line: 223, column: 8, scope: !547)
!547 = distinct !DILexicalBlock(scope: !519, file: !1, line: 223, column: 7)
!548 = !DILocation(line: 223, column: 7, scope: !519)
!549 = !DILocation(line: 224, column: 4, scope: !547)
!550 = !DILocation(line: 226, column: 26, scope: !519)
!551 = !DILocation(line: 226, column: 17, scope: !519)
!552 = !DILocation(line: 226, column: 29, scope: !519)
!553 = !DILocation(line: 226, column: 15, scope: !519)
!554 = !DILocation(line: 227, column: 22, scope: !519)
!555 = !DILocation(line: 227, column: 13, scope: !519)
!556 = !DILocation(line: 227, column: 25, scope: !519)
!557 = !DILocation(line: 227, column: 11, scope: !519)
!558 = !DILocation(line: 228, column: 34, scope: !519)
!559 = !DILocation(line: 228, column: 25, scope: !519)
!560 = !DILocation(line: 228, column: 37, scope: !519)
!561 = !DILocation(line: 228, column: 22, scope: !519)
!562 = !DILocation(line: 230, column: 2, scope: !519)
!563 = !DILocation(line: 230, column: 19, scope: !564)
!564 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 1)
!565 = !DILocation(line: 230, column: 11, scope: !564)
!566 = !DILocation(line: 230, column: 24, scope: !564)
!567 = !DILocation(line: 230, column: 27, scope: !564)
!568 = !DILocation(line: 230, column: 2, scope: !564)
!569 = !DILocation(line: 235, column: 6, scope: !570)
!570 = distinct !DILexicalBlock(scope: !153, file: !1, line: 235, column: 6)
!571 = !DILocation(line: 235, column: 8, scope: !570)
!572 = !DILocation(line: 235, column: 27, scope: !570)
!573 = !DILocation(line: 235, column: 31, scope: !574)
!574 = !DILexicalBlockFile(scope: !570, file: !1, discriminator: 1)
!575 = !DILocation(line: 235, column: 39, scope: !574)
!576 = !DILocation(line: 235, column: 42, scope: !577)
!577 = !DILexicalBlockFile(scope: !570, file: !1, discriminator: 2)
!578 = !DILocation(line: 235, column: 61, scope: !577)
!579 = !DILocation(line: 235, column: 6, scope: !577)
!580 = !DILocation(line: 236, column: 3, scope: !570)
!581 = !DILocation(line: 238, column: 11, scope: !153)
!582 = !DILocation(line: 238, column: 3, scope: !153)
!583 = !DILocation(line: 238, column: 9, scope: !153)
!584 = !DILocation(line: 239, column: 2, scope: !153)
!585 = !DILocation(line: 240, column: 1, scope: !153)
!586 = !DILocalVariable(name: "coder_find", arg: 1, scope: !150, file: !1, line: 300, type: !119)
!587 = !DILocation(line: 300, column: 42, scope: !150)
!588 = !DILocalVariable(name: "filters", arg: 2, scope: !150, file: !1, line: 301, type: !38)
!589 = !DILocation(line: 301, column: 22, scope: !150)
!590 = !DILocalVariable(name: "total", scope: !150, file: !1, line: 303, type: !47)
!591 = !DILocation(line: 303, column: 11, scope: !150)
!592 = !DILocalVariable(name: "i", scope: !150, file: !1, line: 304, type: !60)
!593 = !DILocation(line: 304, column: 9, scope: !150)
!594 = !DILocalVariable(name: "tmp", scope: !595, file: !1, line: 308, type: !60)
!595 = distinct !DILexicalBlock(scope: !150, file: !1, line: 307, column: 2)
!596 = !DILocation(line: 308, column: 10, scope: !595)
!597 = !DILocation(line: 309, column: 22, scope: !598)
!598 = distinct !DILexicalBlock(scope: !595, file: !1, line: 309, column: 7)
!599 = !DILocation(line: 309, column: 7, scope: !598)
!600 = !DILocation(line: 309, column: 37, scope: !598)
!601 = !DILocation(line: 309, column: 7, scope: !595)
!602 = !DILocation(line: 310, column: 4, scope: !598)
!603 = !DILocation(line: 313, column: 2, scope: !150)
!604 = !DILocalVariable(name: "fc", scope: !605, file: !1, line: 314, type: !380)
!605 = distinct !DILexicalBlock(scope: !150, file: !1, line: 313, column: 5)
!606 = !DILocation(line: 314, column: 34, scope: !605)
!607 = !DILocation(line: 315, column: 8, scope: !605)
!608 = !DILocation(line: 315, column: 27, scope: !605)
!609 = !DILocation(line: 315, column: 19, scope: !605)
!610 = !DILocation(line: 315, column: 30, scope: !605)
!611 = !DILocation(line: 316, column: 7, scope: !612)
!612 = distinct !DILexicalBlock(scope: !605, file: !1, line: 316, column: 7)
!613 = !DILocation(line: 316, column: 10, scope: !612)
!614 = !DILocation(line: 316, column: 7, scope: !605)
!615 = !DILocation(line: 317, column: 4, scope: !612)
!616 = !DILocation(line: 319, column: 7, scope: !617)
!617 = distinct !DILexicalBlock(scope: !605, file: !1, line: 319, column: 7)
!618 = !DILocation(line: 319, column: 11, scope: !617)
!619 = !DILocation(line: 319, column: 20, scope: !617)
!620 = !DILocation(line: 319, column: 7, scope: !605)
!621 = !DILocation(line: 326, column: 10, scope: !622)
!622 = distinct !DILexicalBlock(scope: !617, file: !1, line: 319, column: 29)
!623 = !DILocation(line: 327, column: 3, scope: !622)
!624 = !DILocalVariable(name: "usage", scope: !625, file: !1, line: 330, type: !626)
!625 = distinct !DILexicalBlock(scope: !617, file: !1, line: 327, column: 10)
!626 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !47)
!627 = !DILocation(line: 330, column: 19, scope: !625)
!628 = !DILocation(line: 331, column: 8, scope: !625)
!629 = !DILocation(line: 331, column: 12, scope: !625)
!630 = !DILocation(line: 331, column: 29, scope: !625)
!631 = !DILocation(line: 331, column: 21, scope: !625)
!632 = !DILocation(line: 331, column: 32, scope: !625)
!633 = !DILocation(line: 332, column: 8, scope: !634)
!634 = distinct !DILexicalBlock(scope: !625, file: !1, line: 332, column: 8)
!635 = !DILocation(line: 332, column: 14, scope: !634)
!636 = !DILocation(line: 332, column: 8, scope: !625)
!637 = !DILocation(line: 333, column: 5, scope: !634)
!638 = !DILocation(line: 335, column: 13, scope: !625)
!639 = !DILocation(line: 335, column: 10, scope: !625)
!640 = !DILocation(line: 337, column: 2, scope: !605)
!641 = !DILocation(line: 337, column: 19, scope: !642)
!642 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 1)
!643 = !DILocation(line: 337, column: 11, scope: !642)
!644 = !DILocation(line: 337, column: 24, scope: !642)
!645 = !DILocation(line: 337, column: 27, scope: !642)
!646 = !DILocation(line: 337, column: 2, scope: !642)
!647 = !DILocation(line: 341, column: 9, scope: !150)
!648 = !DILocation(line: 341, column: 15, scope: !150)
!649 = !DILocation(line: 341, column: 2, scope: !150)
!650 = !DILocation(line: 342, column: 1, scope: !150)
